
library("RODBC")
stewie.xdb <- odbcDriverConnect(connection = "DSN=stewie_xdb;UID=RFP;PWD=RFP;")

stewie.tables <- function (full=FALSE, ...) {
  temp <- sqlTables(channel=stewie.xdb, ...)
  if ( full == FALSE ) {
    temp <- temp$TABLE_NAME
  } 
  temp
}

stewie.columns <- function (table, full=FALSE, ...) {
  temp <- sqlColumns(channel=stewie.xdb, sqtable=table, ...)
  if ( full == FALSE ) {
    temp <- temp[c("COLUMN_NAME", "TYPE_NAME")]
  }
  temp
}

stewie.query <- function (query, ...) {
  sqlQuery(channel=stewie.xdb, query=query, ...)
}

mod.parm.val <- function (...) {
  query <- c(
             "SELECT a.dg_key,",
             "       a.loc_key,",
             "       a.prod_key,",
             "       a.parm_val as beta,",
             "       b.parm_val as q0,",
             "       c.parm_val as t0,",
             "       d.parm_val as gamma",
             "  FROM mod_parm_val a",
             " INNER JOIN mod_parm_val b",
             "    ON a.dg_key = b.dg_key",
             "   AND a.loc_lvl_key = b.loc_lvl_key",
             "   AND a.prod_lvl_key = b.prod_lvl_key",
             "   AND a.loc_key = b.loc_key",
             "   AND a.prod_key = b.prod_key",
             " INNER JOIN mod_parm_val c",
             "    ON c.dg_key = b.dg_key",
             "   AND c.loc_lvl_key = b.loc_lvl_key",
             "   AND c.prod_lvl_key = b.prod_lvl_key",
             "   AND c.loc_key = b.loc_key",
             "   AND c.prod_key = b.prod_key",
             " INNER JOIN mod_parm_val d",
             "    ON d.dg_key = c.dg_key",
             "   AND d.loc_lvl_key = c.loc_lvl_key",
             "   AND d.prod_lvl_key = c.prod_lvl_key",
             "   AND d.loc_key = c.loc_key",
             "   AND d.prod_key = c.prod_key",
             " WHERE a.parm_id = 'beta'",
             "   AND b.parm_id = 'q0'",
             "   AND c.parm_id = 't0'",
             "   AND d.parm_id = 'gamma'",
             " ORDER BY a.dg_key, a.loc_key, a.prod_key"
             )
  q <- paste(query, collapse=" ")
  mpv <- stewie.query(query=q, ...)

  mpv$DG_KEY = factor(mpv$DG_KEY)
  mpv$PROD_KEY = factor(mpv$PROD_KEY)
  mpv$LOC_KEY = factor(mpv$LOC_KEY)

  mpv
}
