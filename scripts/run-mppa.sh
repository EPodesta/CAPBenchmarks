#
# Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#

# Parameters.
export ITERATIONS=5
export ROOTDIR=$PWD
export RESULTSDIR=$ROOTDIR/results
export BINDIR=$ROOTDIR/bin
export MPPADIR=/usr/local/k1tools

# Create results directory.
rm -f $RESULTSDIR/*
mkdir -p $RESULTSDIR

# Iterations.
for it in {1..$ITERATIONS}; do
	# Kernels.
	for class in tiny small workstation standard large; do
		# Number of clusters.
		for kernel in fn gf is km lu; do
			# Classes.
			for nprocs in 1 2 4 8 16; do
				$MPPADIR/bin/k1-power -- $MPPADIR/bin/k1-jtag-runner --multibinary=$BINDIR/$kernel.mppa.mpk --exec-multibin=IODDR0:$kernel.master -- --verbose --class $class --nthreads $nprocs &>> $RESULTSDIR/$kernel-$class-$nprocs.mppa
			done 
		done
	done
done