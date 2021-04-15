BENCHMARK_ROOT=./
HEATRACE_ROOT=../../heatrace
PROXY_BENCHMARK_ROOT=../../manycore_benchmark

cd ${BENCHMARK_ROOT}/bin/
for pages in 32 42 48 64; do
	cd ..; make clean-x86; make all-x86 PAGES=-DPAGES${pages} -j 8; cd -

	for app in fn gf km is lu; do
		bash ${HEATRACE_ROOT}/run.sh -- ./${app}.intel &>> pin_${pages}pages_overview.out

		mv ${app}.intel.overall.info.csv \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${pages}pages/${app}_sequential_x86_pin_${pages}pages-overall.out
		mv ${app}.intel.stack.trace.csv  \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${pages}pages/${app}_sequential_x86_pin_${pages}pages-stack.out

		mv ${app}.intel.heap.trace.csv   \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${pages}pages/${app}_sequential_x86_pin_${pages}pages-heap.out

		mv ${app}.intel.static.trace.csv \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${pages}pages/${app}_sequential_x86_pin_${pages}pages-static.out
	done;
done
cd -
