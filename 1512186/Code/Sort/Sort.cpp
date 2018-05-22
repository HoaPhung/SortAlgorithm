#include "Sort.h"

void GenerateRandomData(int * a, int n){
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; ++i)
		a[i] = rand() % n;
}

void GenerateSortedData(int * a, int n){
	for (int i = 0; i < n; i++)
		a[i] = i;
}

void GenerateReverseData(int * a, int n){
	for (int i = 0; i < n; ++i)
		a[i] = n - 1 - i;
}

void GenerateNearSortedData(int * a, int n){
	for (int i = 0; i < n; ++i)
		a[i] = i;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; ++i) {
		int r1 = rand() % n;
		int r2 = rand() % n;
		swap(a[r1], a[r2]);
	}
}

void writeFileTxt(string s, int * a, int n){
	ofstream file;
	file.open(s);
	for (int i = 0; i < n; i++)
		file << a[i] << " ";
	file.close();
}

string createNameFile(int alg, int state, int size){
	string nameAlg, nameState, nameSize;
	//create name of algorithms
	switch (alg) {
	case 1: {
		nameAlg = "SelectionSort";
		break;
	}
	case 2: {
		nameAlg = "BubbleSort";
		break;
	}
	case 3: {
		nameAlg = "InsertionSort";
		break;
	}
	case 4: {
		nameAlg = "MergeSort";
		break;
	}
	case 5: {
		nameAlg = "QuickSort";
		break;
	}
	case 6: {
		nameAlg = "HeapSort";
		break;
	}
	case 7: {
		nameAlg = "RadixSort";
		break;
	}
	}

	//create name of state
	switch (state) {
	case 1: {
		nameState = "Random";
		break;
	}
	case 2: {
		nameState = "Sorted";
		break;
	}
	case 3: {
		nameState = "Reverse";
		break;
	}
	case 4: {
		nameState = "NearSorted";
		break;
	}
	}

	//create name of size
	stringstream ss;
	ss << size;
	nameSize = ss.str();

	//create name of file
	string nameFile = nameAlg + "_" + nameState + "_" + nameSize + ".txt";
	return nameFile;
}

float getTime(RunSort run, int*a,int n, int alg, int state){
	float time;
	string nameFile = "";

	switch (state) {
	case 1: {
		GenerateRandomData(a, n);
		break;
	}
	case 2: {
		GenerateSortedData(a, n);
		break;
	}
	case 3: {
		GenerateReverseData(a, n);
		break;
	}
	case 4: {
		GenerateNearSortedData(a, n);
		break;
	}
	}

	switch (alg) {
	case 1: {
		run.setRunSort(new SelectionSort());
		break;
	}
	case 2: {
		run.setRunSort(new BubbleSort());
		break;
	}
	case 3: {
		run.setRunSort(new InsertionSort());
		break;
	}
	case 4: {
		run.setRunSort(new MergeSort());
		break;
	}
	case 5: {
		run.setRunSort(new QuickSort());
		break;
	}
	case 6: {
		run.setRunSort(new HeapSort());
		break;
	}
	case 7: {
		run.setRunSort(new RadixSort());
		break;
	}
	}

	clock_t begin = clock();
	run.getResult(a, n);
	clock_t end = clock();
	nameFile = createNameFile(alg, state, n);
	writeFileTxt(nameFile, a, n);
	time = (float)(end - begin) / CLOCKS_PER_SEC;
	return time;
}

void SelectionSort::sort(int * a, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[minIdx])
				minIdx = j;
		}
		swap(a[i], a[minIdx]);
	}
}

void BubbleSort::sort(int * a, int n){
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j <n-i-1; j++) {
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

void InsertionSort::sort(int * a, int n){
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j>=0 && a[j]>key){
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

void MergeSort::merge(int * a, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L = new int[n1];
	int* R = new int[n2];
	for (i = 0; i < n1; i++)
		L[i] = a[l + i];
	for (j = 0; j < n2; j++)
		R[j] = a[m + 1 + j];

	i = 0; j = 0; k = l; 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		a[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j];
		j++;
		k++;
	}
}

void MergeSort::mergeSort(int * a, int l, int r){
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(a, l, m);
		mergeSort(a, m + 1, r);
		merge(a, l, m, r);
	}
}

void MergeSort::sort(int * a, int n){
	mergeSort(a, 0, n - 1);
}

int QuickSort::partition(int * a, int low, int high){
	int pivot = a[(low + high) / 2];
	int i = low - 1;
	for (int j = low; j <= high - 1; ++j) {
		if (a[j] <= pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[high]);
	return i + 1;
}

void QuickSort::quickSort(int * a, int low, int high){
	/*if (low < high) {
		int pi = partition(a, low, high);
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high);
	}*/
	if (low >= high) return;
	int pivot = a[(low + high) / 2];
	int i = low, j = high;
	do {
		while (a[i] < pivot) ++i;
		while (a[j] > pivot) --j;
		if (i <= j) {
			if (i < j) swap(a[i], a[j]);
			++i;
			--j;
		}
	} while (i <= j);
	quickSort(a, low, j);
	quickSort(a, i, high);
}

void QuickSort::sort(int * a, int n){
	quickSort(a, 0, n - 1);
}

void HeapSort::heapify(int * a, int n, int i){
	int largest = i; //initialize largest as roof
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	//if left child is larger than roof, largest is l
	if (l<n && a[l]>a[largest])
		largest = l;
	//if right child is larger than roof, largest is r
	if (r<n && a[r]>a[largest])
		largest = r;

	// if largest is not roof
	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void HeapSort::sort(int * a, int n){
	// build heap
	for (int i = n / 2; i >= 0; i--)
		heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--) {
		//remove current roof to end
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

int RadixSort::getMax(int * a, int n){
	int max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

void RadixSort::countSort(int * a, int n, int exp){
	//output array
	int* output = new int[n];
	int i, count[10] = { 0 };
	// store coungt of occurrences int count[]
	for (i = 0; i < n; i++)
		count[(a[i] / exp) % 10]++;
	//change count[i], so that count[i] now contain actual
	//position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	//buitd output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}
	//copy the output array to a array
	for (i = 0; i < n; i++)
		a[i] = output[i];
}

void RadixSort::sort(int * a, int n){
	int m = getMax(a, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(a, n, exp);
}

RunSort::RunSort(){
	s = NULL;
}

void RunSort::setRunSort(Sort * _s){
	s = _s;
}

void RunSort::getResult(int * a, int n){
	if (s == NULL)
		return;
	else
		return s->sort(a, n);
}


