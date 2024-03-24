static void quickSortK1K2(std::vector<int>& array, int left, int right, int k1, int k2) {
    if (left >= right)
    {
        return;
    }

    int l = left;
    int r = right;
    int pivot = array[l + (r - l) / 2];

    while (l <= r)
    {
        while (array[l] < pivot)
        {
            ++l;
        }
        while (array[r] > pivot)
        {
            --r;
        }
        if (l >= r)
        {
            break;
        }
        if (l < r)
        {
            std::swap(array[l], array[r]);
            ++l;
            --r;
        }
    }

    if (k1 <= r) {
        quickSortK1K2(array, left, r, k1, k2);
    }
    if (k2 >= r) {
        quickSortK1K2(array, r + 1, right, k1, k2);
    }
}
