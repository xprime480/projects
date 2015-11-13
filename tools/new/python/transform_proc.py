
import TransformationController

import sys
import os.path
import os

# TODO:
#
# Take packages into consideration
# configuration file for constant
#
#

if __name__ == '__main__' :
    indir = '.'
    outdir = '.'
    root = '*'

    args = sys.argv[1:]
    if len(args) :
        indir = args[0]
        args = args[1:]
    if len(args) :
        outdir = args[0]
        args = args[1:]
    if len(args) :
        root = args[0]

    if not os.access(outdir, os.F_OK) :
        print 'creating %s' % outdir
        os.makedirs(outdir)

    tables = [ "/DMF/UREQ_TSTYPE",
               "/DMF/TASK",
               "/DMF/UTASK_CONT",
               "/DMF/UREQ_HIER",
               "/DMF/MSG_HIGH",
               "/DMF/MSG_LOW",
               "/DMF/UMD_PRI" ]

    tc = TransformationController.TransformationController(indir, outdir, tables)
    tc.process(root)
    tc.export()
    tc.make_master(os.path.join(outdir, '..', 'master.sql'))
