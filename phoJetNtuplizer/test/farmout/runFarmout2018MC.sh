#!/bin/bash


datasets=(
    GJets_1j_Gpt-100To250_5f_NLO
    GJets_1j_Gpt-250To400_5f_NLO
    GJets_1j_Gpt-400To650_5f_NLO
    GJets_1j_Gpt-650ToInf_5f_NLO
)

dirName=(
    GJets_1j_Gpt-100To250_5f_NLO
    GJets_1j_Gpt-250To400_5f_NLO
    GJets_1j_Gpt-400To650_5f_NLO
    GJets_1j_Gpt-650ToInf_5f_NLO
)

index=-1;
for sampleName in "${datasets[@]}"; do
    index=$(( $index+1 ))

    inputfiles=private-nlo/$sampleName.in
    
    echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

    farmoutAnalysisJobs \
	--input-files-per-job=20 \
	--input-file-list=${inputfiles} \
	--extra-inputs=Autumn18_V19_MC.db \
	--extra-usercode-files=cfipython \
	--memory-requirements=4000 \
	--assume-input-files-exist \
	--base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \
	${dirName[$index]} \
	/cms/ekoenig4/Ntuples/2018/CMSSW_10_2_18 \
	$PWD/run_102X_mc2018-farmout.py

done


# --memory-requirements=4000 \
    # --assume-input-files-exist \ ##to run for files elsewhere in US
# --skip-existing-output \ ## to resubmit for missing root files

# To use HEP machines only
#--base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \

