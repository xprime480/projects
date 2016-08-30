REMOTE_RD1=/home/i809989/hana_work/RD1_02_DAVISMIC/__empty__/sap/is/ddf/udf/SP_SR_HPR_CALC_GEN_VAR_CONTRIBUTIONS.procedure
LOCAL_RD1=/home/i809989/SAPDevelop/AFL/git/sys/src/AFL/UDF_CORE/hana_content/RD1/sap/is/ddf/udf/SP_SR_HPR_CALC_GEN_VAR_CONTRIBUTIONS.procedure
kdiff3 -m $REMOTE_RD1 $LOCAL_RD1 -o $REMOTE_RD1 
