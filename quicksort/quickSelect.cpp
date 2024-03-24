int quickSelect(int* array, int low, int high, int k)
{
	while (low != high)
	{
		int pivot = array[(low + high) / 2];
		int i = low;
		int j = high;

		while (i <= j)
		{
			while (array[i] < pivot)
			{
				++i;
			}
			while (array[j] > pivot)
			{
				--j;
			}
			if (i <= j)
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
				++i;
				--j;
			}
		}

		if (k <= j)
		{
			high = j;
		}
		else if (k >= i)
		{
			low = i;
		}
		else
		{
			return array[k];
		}
	}

	return array[low];
}
