/**
 * Program to find the maximum possible Sigma(i * A[i])
 * by rotating(shifting) the elements left one place
 * at a time.
 *
 * This current implementation avoids the actual rotation
 * operation to find the maximum possible value, but still
 * is quadratic in running time.
 *
 * @author Rabboni Rabi
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/* Function definitions */
int get_best_rotation_pos(int* input_array, int input_length);
int* rotate_array(int* array, int array_length, int rotation_number);

int main() {

  /* Get the length of array to scan for */
  printf("Enter the length of the array to scan for: \n");

  /* Get the length of input array */
  int n;
  scanf("%d", &n);

  /* Get the input array */
  printf("Enter the array: \n");
  int *input_array;
  input_array = (int*) malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    scanf("%d", &input_array[i]);
  }

  /* Get the number of rotations that will result in best possible value */
  int rotation_number = get_best_rotation_pos(input_array, n);

  int* rotated_array = rotate_array(input_array, n, rotation_number);

  printf("Printing out the rotated array\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", rotated_array[i]);
  }
  printf("\n");

  int sigma = 0;
  for (int i = 0; i < n; i++) {
    sigma+= i * rotated_array[i];
  }
  printf("%s%d\n", "Maximum possible Sigma(i*A[i]) of given array is: ", sigma);


  return 0;
}

/* Function to get the best rotation position:
 * i.e. the rotation number k where
 * sigma(i * A[i]) of the array elements is maximum
 *
 * @param input_array the given array
 * @param input_length the number of elements in the given array
 * @return the rotation number
 */
int get_best_rotation_pos(int* input_array, int input_length) {

  /* variable holding the best increment from the un rotated position */
  int best_inc = 0;

  /* variable holding the rotation number of the best increment */
  int best_inc_rot_no = 0;

  /* Iterate through all possible rotations */
  for (int k = 1; k < input_length; k++) {

    /* variable to hold the incremented sigma(i * A[i]) for the kth rotation*/
    int inc = 0;

    /* Iterate through all elements of the array */
    for (int i = 1; i < input_length; i++) {

      /* Check if kth rotation (shifting) for the value at the index
       * will result in exceeding the array. If so, wrap around. */
      if ((i + k) >= input_length) {
        /* calculate the increment in i*A[i] at ith index after k rotations */
        inc+= i * (input_array[i + k - input_length] - input_array[i]);
      }
      else {
        inc+= i * (input_array[i + k] - input_array[i]);
      }
    }

    /* Check and update the best increment value and index */
    if (inc > best_inc) {
      best_inc = inc;
      best_inc_rot_no = k;
    }
  }

  return best_inc_rot_no;
}


/**
 * Function that shifts the elements in an array to the left
 * by a specified number of rotations.
 * eg: if i is an index and k is the number of rotations, then
 * the value at i + k gets shifted to i.
 *
 * @param array - the array whose elements are to be shifted
 * @param array_length - the length of the array
 * @param rotation_number - the number of leftward rotations (or shifts)
 * @return the rotate array
 */
int* rotate_array(int* array, int array_length, int rotation_number) {

  if (rotation_number == 0) {
    printf("%s\n", "No rotation done on array");
    return array;
  }

  if (rotation_number >= array_length) {
    /* return without performing any shift */
    printf("ERROR: Number of rotations is larger than the length of array\n");
    return array;
  }

  /* Create a temporary array to hold the elements (rotation_number) that will
   * be shifted out and wrapped into the back of the array */
  int *temp_array = (int*) malloc(rotation_number * sizeof(int));

  /* Store the values that will be shifted out in a temporary array */
  for (int i = 0; i < rotation_number; i++) {
    temp_array[i] = array[i];
  }

  /* The array index from which the elements shifted out
   * and saved in the temporary array will be inserted */
  int append_index = array_length - rotation_number;

  /* Shift the elements to the left by the rotation number */
  for (int i = 0; i < append_index; i++) {
    array[i] = array[i + rotation_number];
  }

  /* Insert the elements shifted out to the back of the array */
  for (int i = append_index; i < array_length; i++) {
    array[i] = temp_array[i - append_index];
  }

  /* return the rotated array */
  return array;
}
