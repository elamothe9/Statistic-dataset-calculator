#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void getClass(double* classMin, double* classMax, int classes, int class_number, const double* dataset, const int* size) {
    double class_width = ceil(((dataset[*size - 1] - dataset[0]) / classes));

    printf("Class width: %.3f\n", class_width);

    *classMin = dataset[0] + (class_width * (class_number - 1));
    if (classes == *size) {
        *classMax = dataset[0] + ((class_width * class_number) - .1);
    } else{
        *classMax = dataset[0] + ((class_width * class_number) - 1);

    }
}

// Sorting function using Bubble Sort
void sortDataset(double* dataset, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (dataset[j] > dataset[j + 1]) {
                // Swap dataset[j] and dataset[j + 1]
                double temp = dataset[j];
                dataset[j] = dataset[j + 1];
                dataset[j + 1] = temp;
            }
        }
    }
    for(int j = 0; j < size; j++){
        printf("%.1lf\n", dataset[j]);
    }
}

double* getdataset(int* size) {
    printf("Paste your dataset, one number per line. Press Enter twice to finish:\n");

    double* dataset = (double*)malloc(1000 * sizeof(double));
    if (dataset == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    char input[10000];
    int i = 0;

    // Read multiple lines of input
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '\n') {
            break; // Stop if Enter is pressed on an empty line
        }
        double temp = atof(input); // Convert the string to a double
        dataset[i] = temp;
        i++;
        if (i >= 1000) {
            printf("Reached maximum dataset size (1000 entries).\n");
            break;
        }
    }

    *size = i; // Update the size of the dataset

    // Sort the dataset before returning
    sortDataset(dataset, *size);

    return dataset;
}

double getVariance(int size, double mean,const double* dataset, double* sampleVariance){
    double variance;
    double sumOfSquaredDifferences = 0;
    for(int i = 0; i<size; i++){
        sumOfSquaredDifferences += (dataset[i]-mean)*(dataset[i]-mean);
    }
    variance = sumOfSquaredDifferences/size;
    *sampleVariance = sumOfSquaredDifferences/(size-1);
    return variance;
}


int main(void) {
    int size = 0;
    double* dataset = getdataset(&size);
    int classes;
    printf("How many classes are there? ");
    scanf("%d", &classes);
    int cumulativeFrequency = 0;
    double sampleMean = 0;

    // for loop that prints all the data from each class, one at a time.
    for(int i = 0; i<classes; i++){
        printf("\n\nClass %d:\n", i+1);
        double classMin;
        double classMax;
        getClass(&classMin, &classMax, classes, i+1, dataset, &size);
        printf("Class minimum: %.02lf\n", classMin);
        printf("Class maximum: %.02lf\n", classMax);
        int frequency = 0;
        for(int j = 0; j<size; j++) {
            if (dataset[j] >= classMin && dataset[j] <= classMax) {
                frequency++;
            }
        }
        printf("Frequency: %d\n", frequency);
        double midpoint = ((classMax-classMin)/2) + classMin;
        printf("Midpoint: %.2lf\n", midpoint);
        double relativeFrequency = (double) frequency/size;
        printf("Relative Frequency: %.3lf\n", relativeFrequency);
        cumulativeFrequency += frequency;
        printf("Cumulative Frequency: %d\n", cumulativeFrequency);
        sampleMean += (midpoint*frequency)/size;
    }
    double count = 0;
    for(int i = 0; i<size; i++){
        count += dataset[i];
    }
    printf("\n\nSample size: %d\n", size);
    double mean = count/size;
    printf("Population mean : %.3lf\n", mean);
    printf("Sample mean: %.3lf\n", sampleMean);

    double median;
    if(size %2 == 0){
        median = (dataset[size/2]+dataset[size/2-1])/2;
    } else{
        median = dataset[size/2];
    }
    printf("Median: %.2lf\n", median);
    double range = dataset[size-1]-dataset[0];
    printf("Range: %.3lf\n", range);
    double sampleVariance;
    double populationVariance = getVariance(size, mean, dataset, &sampleVariance);
    printf("Population variance: %.3lf\n", populationVariance);
    double sampleStandardDeviation = pow(sampleVariance, 0.5);
    double populationStandardDeviation = pow(populationVariance, 0.5);
    printf("Sample variance: %.3lf\n", sampleVariance);
    printf("Sample standard deviation: %.3lf\n", sampleStandardDeviation);
    printf("Population standard deviation: %.3lf\n", populationStandardDeviation);
    double cv = (sampleStandardDeviation/mean)*100;
    printf("CV: %.3lf\n", cv);
    printf("+1 standard deviation: %.3lf\n", mean + populationStandardDeviation);
    printf("+2 standard deviation: %.3lf\n", mean + (2* populationStandardDeviation));
    printf("+3 standard deviation: %.3lf\n", mean + (3*populationStandardDeviation));
    printf("-1 standard deviation: %.3lf\n", mean - populationStandardDeviation);
    printf("-2 standard deviation: %.3lf\n", mean - (2*populationStandardDeviation));
    printf("-3 standard deviation: %.3lf\n", mean - (3*populationStandardDeviation));


    free(dataset);
    return 0;
}

