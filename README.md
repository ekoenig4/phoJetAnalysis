#MiniAOD analyzer for all physics objects 

Instructions:
```
cmsrel CMSSW_10_2_18
cd CMSSW_10_2_18/src
cmsenv
git cms-init

#https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#How_to_run_ecal_BadCalibReducedM
git cms-addpkg RecoMET/METFilters
 
#https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#102X
git cms-merge-topic cms-egamma:PhotonIDValueMapSpeedup1029
scram b -j 8
git clone git@github.com:cms-egamma/EgammaPostRecoTools.git  EgammaUser/EgammaPostRecoTools
cd  EgammaUser/EgammaPostRecoTools
git checkout master
cd -

git clone https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

Electrons and Photons:
```
[] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#102X
```
JetMET
```
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
[] https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#2017_Data
[] https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_or_10
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox
```

Taus:
```
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/TauIDRecommendationForRun2
[] https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[] https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf
[] https://indico.cern.ch/event/810741/contributions/3384093/attachments/1827349/2991114/TauID_CMSweek_10042019.pdf 
```
Muons:
```
[] https://twiki.cern.ch/twiki/bin/view/CMS/MuonPOG
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
```

For PPD RunII analysis recipe
```
[] https://twiki.cern.ch/twiki/bin/view/CMS/PdmV
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
```
