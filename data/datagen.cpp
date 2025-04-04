#include <fstream>
#include <vector>
#include <random>

int main(){
	/* set parameters */
	const std::size_t n_data = 1000;
	const float x_min = 0.0;
	const float x_max = 100.0;

	/* generate x vector */
	std::vector<double> xvec(n_data);
	for(std::size_t i=0; i<n_data; i++){
		xvec[i] = x_min + i * (x_max - x_min)/n_data;
	}	
	
	/* compute baseline values for y vector */
	// In this case, we have yvec = 0.5 * xvec - 2.0 (a linear function)
	const double slope = 0.5;
	const double interc = -2.0;

	std::vector<double> yvec(xvec.size());
	std::transform(xvec.begin(), xvec.end(), 
				   yvec.begin(), 
				   [slope, interc](double xi){ return slope * xi + interc; }
	); 

	/* generate noise */
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 10.0);
 
    std::vector<int> noise(yvec.size());
 
    for (int& num : noise) {
        num = dist(gen);
    }

	/* add noise to yvec */
	std::vector<double> yvec_hat(yvec.size());
	std::transform(yvec.begin(), yvec.end(), noise.begin(), 
				   yvec_hat.begin(), 
				   [](double yi, double ni){ return yi + ni; } 
	);

	/* write data to file */
	std::ofstream file("data.csv");
	for(std::size_t j = 0; j < n_data; j++){
		file << xvec[j] << "," << yvec_hat[j] << "\n";
	}
	file.close();
	return 0;
}
