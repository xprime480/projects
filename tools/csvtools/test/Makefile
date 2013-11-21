
.PHONY : test

AC_TESTER    = ./ac_tester.sh
EC_TESTER    = ./ec_tester.sh
DK_TESTER    = ./dk_tester.sh
KC_TESTER    = ./kc_tester.sh	

test :
	$(AC_TESTER) one_column_of_integers
	$(AC_TESTER) one_column_of_floats
	$(AC_TESTER) one_column_of_text
	$(AC_TESTER) one_column_of_flags
	$(AC_TESTER) three_columns
	$(AC_TESTER) multiple_date_formats

	$(EC_TESTER) ec_sample_data 1 COLUMN_ONE COLUMN_ONE
	$(EC_TESTER) ec_sample_data 2 COLUMN_ONE COLUMN_TWO

	$(DK_TESTER) three_columns STR_DATA INT_DATA

	$(KC_TESTER) three_columns INT_DATA,STR_DATA



