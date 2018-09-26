#ifndef phoJetNtuplizer_h
#define phoJetNtuplizer_h

// system include files
#include <memory>
// user include files
#include "TTree.h"
#include "Math/VectorUtil.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
//GenInfo
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//Trigger
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
//Photons
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
//Electrons
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
//Jet
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//MET
#include "DataFormats/PatCandidates/interface/MET.h"
//Muons
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
//Taus
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "TLorentzVector.h"
#include <vector>
#include <memory>

using namespace std;

void setbit(UShort_t& x, UShort_t bit);
void setbit(ULong64_t& x, UShort_t bit);

class phoJetNtuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources>{
  public:
    explicit phoJetNtuplizer(const edm::ParameterSet&);
    ~phoJetNtuplizer();

  private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

    // ----------member data ---------------------------
    void branchEventInfo (TTree*);
    void branchPhotons   (TTree*);
    void branchJets      (TTree*);
    void branchElectrons (TTree*);
    void branchMuons     (TTree*);
    void branchTaus      (TTree*);
    void branchMet       (TTree*);
    void branchGenInfo   (TTree*);

    void fillEventInfo  (const edm::Event&, const edm::EventSetup&);
    void fillPhotons    (const edm::Event&, const edm::EventSetup&);
    void fillJets       (const edm::Event&, const edm::EventSetup&);
    void fillElectrons  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
    void fillMuons      (const edm::Event&, math::XYZPoint&, const reco::Vertex);
    void fillTaus      (const edm::Event&);
    void fillMet        (const edm::Event&, const edm::EventSetup&);
    void fillGenInfo    (const edm::Event&);

    void initEventInfo();
    void initPhotons();
    void initJets();
    void initElectrons();
    void initMuons();
    void initTaus();
    void initMet();
    void initGenInfo();

    bool isData_;
    bool debug_;

    bool                                             runEventInfo_;
    edm::EDGetTokenT<double>                         rhoToken_;
    edm::EDGetTokenT<double>                         rhoCentralToken_;
    edm::EDGetTokenT<reco::VertexCollection>         vtxToken_;

    //Trigger Info
    edm::EDGetTokenT<edm::TriggerResults>                    trgResultsToken_;
    edm::EDGetTokenT<edm::TriggerResults>                    patTrgResultsToken_;
    std::string                                              trgResultsProcess_;
    HLTPrescaleProvider                                      hltPrescaleProvider_;

    //Photon Info
    bool                                             runPhotons_;
    edm::EDGetTokenT<edm::View<pat::Photon> >        photonToken_;

    edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
    edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
    edm::EDGetTokenT<EcalRecHitCollection>           esReducedRecHitCollection_;

    //Jet Info
    bool                                             runJets_;
    bool                                             runJetWidthCalculator_;
    edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK4Token_;

    //Electron Info
    bool                                             runEle_;
    edm::EDGetTokenT<edm::View<pat::Electron> >      electronToken_;
    edm::EDGetTokenT<pat::PackedCandidateCollection> packedPFCandsToken_;

    //Muon Info
    bool                                             runMuon_;
    edm::EDGetTokenT<edm::View<pat::Muon> >          muonToken_;

    //Taus Info
    bool                                             runTaus_;
    //edm::EDGetTokenT<edm::View<pat::Tau> >          tausToken_;
    edm::EDGetTokenT<vector<pat::Tau> >              tausToken_;

    //MET Info
    bool                                             runMet_;
    edm::EDGetTokenT<edm::View<pat::MET> >           pfmetToken_;

    //Gen Particle Info
    bool                                             runGenInfo_;
    edm::EDGetTokenT<GenEventInfoProduct>            generatorToken_;
    edm::EDGetTokenT<LHEEventProduct>                lheEventToken_;
    edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
    edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesToken_;

    TTree * tree_;
};

#endif
