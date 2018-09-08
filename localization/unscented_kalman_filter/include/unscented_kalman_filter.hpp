//
// Created by forrest on 18-9-8.
//

#ifndef UNSCENTED_KALMAN_FILTER_UNSCENTED_KALMAN_FILTER_HPP
#define UNSCENTED_KALMAN_FILTER_UNSCENTED_KALMAN_FILTER_HPP

#include "Eigen/Dense"

using Eigen::MatrixXd;

namespace cpp_robotics {

    class UKF {
    public:
        UKF();
        ~UKF();

    private:

        MatrixXd generateSigmaPoints(const MatrixXd& xEst,
                                     const MatrixXd& PEst,
                                     const MatrixXd& gamma);
        /**
         * @brief   get observation
         * @arg     MatrixXd u(2, 1) - robot ctrl speed
         * @arg     MatrixXd xTrue(4, 1) - robot true state
         * @arg     MatrixXd z(1, 2) - sensor observation robot state
         * @arg     MatrixXd xd(4, 1) - robot state with noise robot input
         * @arg     MatrixXd ud(2, 1) - noise robot ctrl speed
         */
        void observation(const MatrixXd& u,
                         MatrixXd& xTrue,
                         MatrixXd& z,
                         MatrixXd& xd,
                         MatrixXd& ud);

        /**
         * @brief   observation Model
         * @arg     MatrixXd x(4, 1)
         * @return  MatrixXd(2, 1)
         */
        MatrixXd observationModel(const MatrixXd& x);

        /**
         * @brief   robot motion mode
         * @arg     MatrixXd x(4, 1) - robot state
         * @arg     MatrixXd u(2, 1) - robot ctrl speed
         * @return  MatrixXd(4, 1) - new robot state
         */
        MatrixXd motionModel(const MatrixXd& x, const MatrixXd& u);

        /**
         * @brief   get robot ctrl speed(v,w) input
         * @return  MatrixXd(2, 1) - robot ctrl speed
         */
        MatrixXd calcInput();

        inline double randu() {
            return (double) rand()/RAND_MAX;
        }

        inline double randn2(double mu, double sigma) {
            return mu + (rand()%2 ? -1.0 : 1.0)*sigma*pow(-log(0.99999*randu()), 0.5);
        }

        inline double randn() {
            return randn2(0, 1.0);
        }

        // Estimation parameter of UKF
        MatrixXd Q_;
        MatrixXd R_;

        // Simulation parameter
        MatrixXd Qsim_;
        MatrixXd Rsim_;

        const double DT = 0.1;  // time tick [s]
        const double SIM_TIME = 50.0;   // simulation time [s]

        // UKF Parameter
        const double ALPHA = 0.001;
        const double BETA = 2;
        const double KAPPA = 0;

        bool show_animation_ = true;
    };

} // namespace cpp_robotics

#endif //UNSCENTED_KALMAN_FILTER_UNSCENTED_KALMAN_FILTER_HPP
