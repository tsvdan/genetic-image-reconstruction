#ifndef ELLIPSEPOPULATION_H
#define ELLIPSEPOPULATION_H

#include "apopulation.h"
#include "ellipsesln.h"

template <int num_elements, int num_slns>
class EllipsePopulation : APopulation<EllipseSln<num_elements>, num_slns>
{
public:
    EllipsePopulation() : ORIGINAL(cv::Mat::zeros(100, 100, CV_8UC3)) {}
    // :ui(...) part of constructor fails w/o
    // now also an undefined reference
    // very large mat (but irrelevant(?))
    
    // Not very smart, cuz
    EllipsePopulation(const cv::Mat& img) : ORIGINAL(img) {
        //population = std::vector<EllipseSln<num_elements>>(num_slns);
        population.reserve(num_slns);
        for (int i = 0; i < num_slns; ++i) {
            population.emplace_back(EllipseSln<num_elements>(img));
        }
    }

    //EllipsePopulation& operator=(EllipsePopulation&& elp) = default;

    EllipsePopulation<num_elements, num_slns>& operator=(const EllipsePopulation<num_elements, num_slns>&& pop) {
        this->population = pop.population;
        this->ORIGINAL = pop.ORIGINAL;
        return *this;
    }

    EllipsePopulation<num_elements, num_slns>& operator=(const EllipsePopulation<num_elements, num_slns>& pop) {
        this->population = pop.population;
        this->ORIGINAL = pop.ORIGINAL;
        return *this;
    }

    EllipseSln<num_elements>& operator[](int i) {
        return population[i];
    }

    void selection(const cv::Mat& fit_mat);
    void crossover() override;  
    void mutate_all() override;
    cv::Mat draw_best() {
        auto& best = population[num_slns - 1];
        best._temp.copyTo(best._image);
        best.draw();
        cv::Mat bestest_art = best._image.clone();
        restore_all();
        return bestest_art;
    }

    void restore_all() {
        for (auto& sln : population){
            sln._temp.copyTo(sln._image);
        }
    }  // restore inner state; should be separate

    cv::Mat ORIGINAL;  // can't have it const
    //cv::Mat BESTEST;  //  careful

    mutable std::vector<EllipseSln<num_elements>> population;
private:
};

template <int num_elements, int num_slns>
inline void EllipsePopulation<num_elements, num_slns>::selection(const cv::Mat& fit_mat) {

    for (auto& sln : population) {
        sln.draw();
    } // Necessary to init fitness

    // init fitness and call that;
    std::sort(population.begin(), population.end(), 
              [this, &fit_mat](const EllipseSln<num_elements>& _first,
                 const EllipseSln<num_elements>& _second) -> bool
               { return _first.fitness(fit_mat) < _second.fitness(fit_mat); });

    EllipseSln<num_elements> fittest = population[num_slns - 1];
    std::vector<EllipseSln<num_elements>> _t_pop{population};
    int s = 0;
    while (s < num_slns - 1){
        int i = randint(0, num_slns - 1);
        if (randint(0, num_slns) < i) {
            _t_pop[s] = population[i];
            ++s;
        }
    }


    population[num_slns - 2] = EllipseSln<num_elements>(fittest);
    population[num_slns - 1] = EllipseSln<num_elements>(fittest);
    population[num_slns - 2].mutate();

    for (int i = 0; i < num_slns - 2; ++i) {
        std::vector<Ellipse> cur_sln = _t_pop[i].elements;
        std::vector<Ellipse> new_sln;
        new_sln.reserve(num_elements);
        for (int k = 0; k < num_elements / 2; k += 2) {
            int e1 = randint(0, num_elements - 1);     // 3(4) times
            int e2 = randint(0, num_elements - 1);    // change to lambda
            Ellipse el1(cur_sln[e1]);
            Ellipse el2(cur_sln[e2]);

            // Crossover
            Ellipse::crossover(el1, el2);
            new_sln.push_back(el1);
            new_sln.push_back(el2);
        }
        while (new_sln.size() < num_elements) {
            new_sln.push_back(cur_sln[randint(0, num_elements-1)]);
        } // should happen only once for odd n_el
        population[i].elements = new_sln;
    }

    crossover();
    mutate_all();
}


template <int num_elements, int num_slns>
inline void EllipsePopulation<num_elements, num_slns>::crossover() {
}


template <int num_elements, int num_slns>
inline void EllipsePopulation<num_elements, num_slns>::mutate_all() {
    for (auto& member : population)
        member.mutate();
}


#endif // ELLIPSEPOPULATION_H
