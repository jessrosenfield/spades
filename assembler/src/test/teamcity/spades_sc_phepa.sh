#!/bin/bash

############################################################################
# Copyright (c) 2011-2012 Saint-Petersburg Academic University
# All Rights Reserved
# See file LICENSE for details.
############################################################################

set -e
pushd ../../../

rm -rf /tmp/data/output/spades_output/PHEPARINUS

#./spades_compile.sh
./spades.py --sc -m 160 -k 21,33,55 --12 data/input/P.heparinus/Phe_no7.fastq.gz -o /tmp/data/output/spades_output/PHEPARINUS

rm -rf ~/quast-1.3/PHEPARINUS/

python ~/quast-1.3/quast.py -R data/input/E.coli/MG1655-K12.fasta.gz -G data/input/E.coli/genes/genes.gff -O data/input/E.coli/genes/operons.gff -o ~/quast-1.3/PHEPARINUS/ /tmp/data/output/spades_output/PHEPARINUS/contigs.fasta

python src/test/teamcity/assess.py ~/quast-1.3/PHEPARINUS/transposed_report.tsv 275000 6 4171 98.1 7.0 0.9
exitlvl=$?
popd

