#include <splat/unreachable.h>
#include <itlib/rand_dist.hpp>
#include <bit>

#define PICOBENCH_IMPLEMENT
#include <picobench/picobench.hpp>

struct arvec {
    float f[3];

    float operator[](int i) const {
        return f[i];
    }
};

struct cvec {
    float x, y, z;
    float operator[](int i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: SPLAT_UNREACHABLE();
        }
    }
};

struct ubvec {
    float x, y, z;
    float operator[](int i) const {
        return reinterpret_cast<const float*>(this)[i];
    }
};

template <typename Vec>
void bench_vec(picobench::state& s) {
    std::mt19937 rng(42);
    itlib::fast_uniform_real_distribution coord_dist(-1.0f, 1.0f);
    std::vector<Vec> vecs;
    for (int i = 0; i < s.iterations(); ++i) {
        vecs.push_back(
            Vec{coord_dist(rng), coord_dist(rng), coord_dist(rng)}
        );
    }

    double sum = 0.0;

    itlib::uniform_uint_max_distribution index_dist(2u);
    for (auto i : s) {
        auto index = index_dist(rng);
        auto& v = vecs[i];
        sum += v[index];
    }

    s.set_result(std::bit_cast<uintptr_t>(sum));
}

PICOBENCH(bench_vec<arvec>);
PICOBENCH(bench_vec<cvec>);
PICOBENCH(bench_vec<ubvec>);

int main(int argc, char* argv[]) {
    picobench::runner r;
    r.set_compare_results_across_samples(true);
    r.set_compare_results_across_benchmarks(true);
    r.set_default_state_iterations({10'000, 1'000'000});
    r.parse_cmd_line(argc, argv);
    return r.run();
}
