// Функция разделения Хоара
int hoarePartition(std::vector<double>& vec, int low, int high) {
    int pivot = vec[low];  // выбор крайнего левого элемента в качестве опорного
    int i = low - 1, j = high + 1;

    while (true) {
        // Находим левый элемент, который больше или равен опорному
        do {
            i++;
        } while (vec[i] < pivot);

        // Находим правый элемент, который меньше или равен опорному
        do {
            j--;
        } while (vec[j] > pivot);

        // Если два указателя встретились, возвращаем индекс разделения
        if (i >= j) {
            return j;
        }

        // Меняем элементы местами
        std::swap(vec[i], vec[j]);
    }
}

// Реализация быстрой сортировки с разбиением Хоара
void quicksortHoare(std::vector<double>& vec, int low, int high) {
    if (low < high) {
        // Получаем индекс разделения
        int pi = hoarePartition(vec, low, high);

        // Отдельно сортируем элементы до разделения и после разделения
        quicksortHoare(vec, low, pi);
        quicksortHoare(vec, pi + 1, high);
    }
}
