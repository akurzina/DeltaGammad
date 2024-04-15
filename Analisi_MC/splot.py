import os
import argparse
import json
import cppyy

from ROOT import (
    RooExponential,
    RooIpatia2,
    RooNumber,
    TFile,
    kBlack,
    TCanvas,
    TObject,
    addProductToTree,
    addSWeightToTree
    )

from P2VV.RooFitWrappers import (
    RealVar,
    Pdf,
    Component,
    buildPdf,
    RooObject,
    Category,
    )

from P2VV.Utilities.SWeights import SData
from P2VV.Utilities.Plotting import plot
from ROOT import gROOT
gROOT.SetBatch(1)

ROOINF = RooNumber.infinity()

TRIGGER_TYPES = {'biased': 'hlt1b==1',
                'unbiased': 'hlt1b==0',
                'noTrigCat': ''}

FIT_OPTS = dict(
        NumCPU=4,
        Timer=1,
        Save=True,
        Verbose=False,
        Optimize=2,
        Minimizer='Minuit2')


def read_params(params_to_fix_file):
    with open(params_to_fix_file, 'r') as stream:
        return json.load(stream)


def ipatia_exp(data, mass, mass_range, mode, background, trig_type):

    if 'Bd' in mode:
        alpha1_value = 1.1#2.15
        alpha1_max = 10
        alpha2_value = 2.5#2.34
        alpha2_max = 10
        n1_value = 2.4
        n2_value = 3.3
        if trig_type=='noTrigCat':
            sigma_value = 9.4
            m_sig_lambda_value =-2.1
            gamma_value = -0.0011
            s_yield = 0.82*data.sumEntries()
            b_yield = 0.18*data.sumEntries()
        elif trig_type=='biased':
            sigma_value = 9.3
            m_sig_lambda_value =-2.7
            gamma_value = -0.001
            s_yield = 0.77*data.sumEntries()
            b_yield = 0.03*data.sumEntries()
        else:
            sigma_value = 9.1
            m_sig_lambda_value =-2.6
            gamma_value = -0.0011
            s_yield = 0.7*data.sumEntries()
            b_yield = 0.03*data.sumEntries()

    if 'Bu' in mode:
        sigma_value = 11.2
        m_sig_lambda_value =-2.65
        alpha1_max = 5
        alpha2_value = 2.23
        alpha2_max = 5
        n1_value = 2.83
        n2_value = 3.14
        gamma_value = -0.001
        if trig_type=='noTrigCat':
            alpha1_value = 2.2 #1.99
            s_yield = 0.40*data.sumEntries()
            b_yield = 0.60*data.sumEntries()
        elif trig_type=='biased':
            alpha1_value = 2.2 #1.99
            s_yield = 0.35*data.sumEntries()
            b_yield = 0.02*data.sumEntries()
        else:
            alpha1_value = 2.35 #1.99
            if 'MC_Bu' in mode:
              s_yield = 0.77*data.sumEntries()
              b_yield = 0.003*data.sumEntries()
            else:
              s_yield = 0.9*data.sumEntries()
              b_yield = 0.09*data.sumEntries()

    # signal
    mean = RealVar(f'mean_{trig_type}', Unit='MeV', Value=5279.9, MinMax=mass_range)
    sigma = RealVar(f'sigma_{trig_type}', Unit='MeV', Value=sigma_value, MinMax=(3, 20))
    m_sig_lambda = RealVar(f'm_sig_lambda_{trig_type}', Title='B Mass resolution lambda', Value=m_sig_lambda_value, MinMax=(-6, 2))
    m_sig_zeta = RealVar(f'm_sig_zeta_{trig_type}', Title='B Mass resolution zeta', Value=0)
    m_sig_beta = RealVar(f'm_sig_beta_{trig_type}', Title='B Mass resolution beta', Value=0)
    alpha1 = RealVar(f'alpha1_{trig_type}', Value=alpha1_value, MinMax=(1, alpha1_max))
    alpha2 = RealVar(f'alpha2_{trig_type}', Value=alpha2_value, MinMax=(1, alpha2_max))
    n1 = RealVar(f'n1_{trig_type}', Value=n1_value, MinMax=(1, 5))#10
    n2 = RealVar(f'n2_{trig_type}', Value=n2_value, MinMax=(1, 5))#10
    pdf_s = Pdf(Name=f'pdf_s_{trig_type}', Type=RooIpatia2, Parameters=(mass, m_sig_lambda, m_sig_zeta, m_sig_beta, sigma, mean, alpha1, n1, alpha2, n2))

    # background
    if background:
        gamma = RealVar(f'gamma_{trig_type}', Value=gamma_value, MinMax=(-1, 1))
        pdf_b = Pdf(Name=f'pdf_b_{trig_type}', Type=RooExponential, Parameters=(mass, gamma))
        tot = data.sumEntries()
        signal = Component(f'signal_{trig_type}', (pdf_s, ), Yield=(s_yield, 0, tot))
        background = Component(f'background_{trig_type}', (pdf_b, ), Yield=(b_yield, 0, tot))
        pdf = buildPdf(Components=(signal, background), Observables=[mass], Name=f'pdf_{trig_type}')
        return pdf

    return pdf_s


def plot_mass(data, mode, mass, pdf, prefix, plots_loc=''):
    nBins = 140
    mass_canvas = TCanvas(f'mass_data_{prefix}', f'mass_data_{prefix}', 1200, 800)
    frames = plot(
        mass_canvas,
        mass,
        data=data,
        pdf=pdf,
        dataOpts=dict(MarkerSize=0.8, MarkerColor=kBlack),
        frameOpts=dict(Bins=nBins),
        plotResidHist=True)
    title = '#it{m(J/#psi K^{+}#pi^{#minus})} [MeV/#it{c}^{2}]' if 'Bd' in mode \
       else '#it{m(J/#psi K^{+})} [MeV/#it{c}^{2}]'
    frames[1].GetXaxis().SetTitle(title)
    frames[0].GetYaxis().SetTitle('Events / (%3.2f MeV/#it{c}^{2})' % ((mass.getMax()-mass.getMin())/float(nBins)))
    if plots_loc: mass_canvas.Print(os.path.join(plots_loc, f'mass_fit_data_{prefix}.pdf'))


def mass_fit_ipatia(input_file, input_tree_name, input_weight_name, output_file,
    output_file_tmp, output_tree_name, mode, trigcat, mass_range, params_to_fix_file,
    params_to_fix_list, background, fit_result_file, plots_loc, add_sweights):

    ws = RooObject(workspace='mass_fit_ipatia').ws()
    # create observables
    observables = [RealVar('index', Title='event index', Observable=True, Value=0, MinMax=(-ROOINF, +ROOINF))]
    if input_weight_name:
        observables += [RealVar(input_weight_name, Title='event weight', Observable=True, Value=0, MinMax=(-ROOINF, +ROOINF))]
    if trigcat:
        hlt1b = Category('hlt1b', Title='Biased trigger', States={'biased': +1, 'unbiased': 0})
        observables += [hlt1b]
    mass = RealVar('B_ConstJpsi_M_1',
        Title='m(J/#psi K^{+}#pi^{#minus})' if 'Bd' in mode else 'm(J/#psi K^{+})',
        Unit='MeV/c^{2}',
        Observable=True,
        Value=5280,
        MinMax=mass_range)
    observables += [mass]

    # read n-tuple file(s)
    dataTreeFile = TFile.Open(input_file)
    dataTree = dataTreeFile.Get(input_tree_name)

    # create data set from nTuple
    data = dataTree.buildDataSet(
        Observables=observables,
        Name=mode,
        Title=mode,
        IndexName='index',
        WeightName=input_weight_name if input_weight_name else '',
        Cuts=f'B_ConstJpsi_M_1 > {mass_range[0]} && B_ConstJpsi_M_1 < {mass_range[1]}')

    # read parameters to be fixed in the fit
    params_to_fix = read_params(params_to_fix_file) if params_to_fix_file else None
    pars_dict = {} if fit_result_file else None

    # fit J/psiKK mass distributions
    if add_sweights:
        output_tf_tmp = TFile(output_file_tmp, 'recreate')
        tree_with_sw = dataTree.CopyTree(f'B_ConstJpsi_M_1 > {mass_range[0]} && B_ConstJpsi_M_1 < {mass_range[1]}')
        sufixes = cppyy.gbl.std.vector('TString')()

    types = ['biased', 'unbiased'] if trigcat else ['noTrigCat']
    for trig_type in types:

        pdf = ipatia_exp(data, mass, mass_range, mode, background, trig_type)
        pdf_pars = pdf.getParameters(data)
        trigCut = TRIGGER_TYPES[trig_type]
        ds = data.reduce(trigCut) if trigcat else data
        # if fix parameters in the fit
        if params_to_fix:
            cat_params = params_to_fix[trig_type]
            # if fix parameters in the fit
            for par in params_to_fix_list:
                mc_param = [p for p in cat_params if par in p['Name']][0]
                par_name = mc_param['Name']
                pdf_pars.find(par_name).setVal(mc_param['Value'])
                pdf_pars.find(par_name).setConstant(True)
                print('Setting parameter', par_name, 'to constant with value', mc_param['Value'])

        result = pdf.fitTo(ds, **FIT_OPTS)
        
        result.Print('v')
        plot_mass(ds, mode, mass, pdf, trig_type, plots_loc)

        if add_sweights:
            sdata = SData(Name='splot_'+trig_type, Pdf=pdf, Data=ds)
            addSWeightToTree(sdata.data('signal_'+trig_type), tree_with_sw, f'sw_{trig_type}', trigCut)
            sufixes.push_back(f'sw_{trig_type}')

        # write parameters to dictionary
        pars_dict.update({trig_type: [{'Name': param.GetName(),
                                       'Value': param.getVal(),
                                       'Error': param.getError()} for param in pdf_pars]})

    # save fit result to file
    if fit_result_file:
        with open(fit_result_file, 'w') as f:
            json.dump(pars_dict, f, indent=4)

    # Store n-tuple in ROOT file.
    if add_sweights:
        addProductToTree(tree_with_sw, sufixes, 'sw')
        for trig_type in types:
            tree_with_sw.SetBranchStatus(f'sw_{trig_type}', 0)
        output_reduced_file = TFile(output_file, 'recreate')
        tree_with_sw_reduced = tree_with_sw.CloneTree()
        tree_with_sw_reduced.Write(output_tree_name, TObject.kOverwrite)
        output_reduced_file.Close()
        print('sWeighted nTuple is saved: ', output_reduced_file)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--input-file', help='Path to the input file')
    parser.add_argument('--input-tree-name', default='DecayTree' , help='Name of the tree')
    parser.add_argument('--input-weight-name', default='' , help='Name of the input weight if any')
    parser.add_argument('--output-file', help='Output ROOT file')
    parser.add_argument('--output-file-tmp', help='Path to the temp output file so save sweights')
    parser.add_argument('--output-tree-name', default='DecayTree', help='Name of the tree')
    parser.add_argument('--mode', help='Name of the selection in yaml')
    parser.add_argument('--trigcat', action='store_true', help='Split tuple in trigger category if specified')
    parser.add_argument('--mass-range', nargs='+', type=int, default=(5210, 5350), help='Specify mass range for the fit')
    parser.add_argument('--background', action='store_true', help='Add exponential background?')
    parser.add_argument('--params-to-fix-file', help='Yaml with dict of parameter names and values')
    parser.add_argument('--params-to-fix-list', nargs='+', help='Yaml with list of parameter names to be fixed from params-to-fix-file')
    parser.add_argument('--fit-result-file', help='To which file to save fit result')
    parser.add_argument('--plots-loc', help='Where to store plots')
    parser.add_argument('--add-sweights', action='store_true', help='Calculate and add sweights if specified')
    args = parser.parse_args()
    mass_fit_ipatia(**vars(args))


