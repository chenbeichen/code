bool checkPossibility(int* nums, int numsSize) {
    if (numsSize < 3) {
        return true;
    }
    int changeCount = 0;
    if (nums[0] > nums[1]) {
        nums[0] = nums[1];
        changeCount++;
    }
    for (int i = 1; i < numsSize - 1; i++) {
        int right = nums[i+1];
        if (nums[i] > right) {
            changeCount++;
            if (changeCount > 1) {
                return false;
            }
            int left = nums[i-1];
            if (left > right) {
                nums[i+1] = nums[i];
            } else {
                nums[i] = left;
            }
        }
    }
    return true;
}