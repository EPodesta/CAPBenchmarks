BENCHMARK_ROOT=./
HEATRACE_ROOT=../../heatrace
PROXY_BENCHMARK_ROOT=../../manycore_benchmark

cd ${BENCHMARK_ROOT}/bin/
for commit in 03de5 aca12 9c021 a9826; do
	git checkout "${commit}";
	NUMBER_PAGES=$(git show "${commit}" | grep "pages setup" | awk '{print $1}')

	cd ..; make clean-x86; make all-x86; cd -

	for app in fn gf km is lu; do
		bash ${HEATRACE_ROOT}/run.sh -- ./${app}.intel &>> pin_${NUMBER_PAGES}pages_overview.out

		mv ${app}.intel.overall.info.csv \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${NUMBER_PAGES}pages/${app}_sequential_x86_pin_${NUMBER_PAGES}pages-overall.out
		mv ${app}.intel.stack.trace.csv  \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${NUMBER_PAGES}pages/${app}_sequential_x86_pin_${NUMBER_PAGES}pages-stack.out

		mv ${app}.intel.heap.trace.csv   \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${NUMBER_PAGES}pages/${app}_sequential_x86_pin_${NUMBER_PAGES}pages-heap.out

		mv ${app}.intel.static.trace.csv \
		   ${PROXY_BENCHMARK_ROOT}/${app}_sequential_x86_pin_${NUMBER_PAGES}pages/${app}_sequential_x86_pin_${NUMBER_PAGES}pages-static.out
	done;
done
cd -
