
def bubblesort(unsorted, first="lowest"):

	completed_elements = 0
	length = len(unsorted)

	while True:

		if completed_elements >= len(unsorted):
			break

		for index in range(length - completed_elements - 1):

			# If next element < or > current element, swap them
			if first == "highest":
				if(unsorted[index + 1] > unsorted[index]):
					unsorted[index + 1], unsorted[index] = unsorted[index], unsorted[index + 1]

			else:
				if(unsorted[index + 1] < unsorted[index]):
					unsorted[index + 1], unsorted[index] = unsorted[index], unsorted[index + 1]


		completed_elements += 1

	return unsorted

if __name__ == "__main__":

	import sys

	unsorted = sys.argv[1:]

	if len(unsorted) < 1:
		print "Please supply your array as command line arguments, one element at a time"
		exit()

	print bubblesort(unsorted)
