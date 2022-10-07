# Data Memory

DataMemory corresponds to a folder in "\data" directory and it simulates the persistence of data that the diagnostic component (Supervisor) would have in practice. All data stored in this element is inserted into 2 *csv* files: *HistoricalData.csv* and *HistoricalMetrics.csv*.

As the names suggest, the first file contains the input/output data obtained from all tests performed by the Supervisor component, while the second file stores the clustering metrics obtained from such tests. In both cases, the data is mapped to its respective occurrence iterations.

The data structure adopted in each of these files is described below.

## *HistoricalData.csv*'s structure

**Separator Character:** "," (comma)

| Column Position  | Meaning | Data Type |
| ------------- | ------------- | ------------- |
| 0  | `iteration`  | `double`|
| 1  | `fuse_test` (input)  |  `double` |
| 2  | `fuse_result` (output) |  `double`|

## *HistoricalMetrics.csv*'s structure

**Separator Character:** "," (comma)

| Column Position  | Meaning | Data Type |
| ------------- | ------------- | ------------- |
| 0  | `iteration`  | `double`|
| 1  | `silhouette of cluster 1`  |  `double` |
| 2  | `silhouette of cluster 2` |  `double`|
| 3  | `number of points in cluster 1` |  `double`|
| 4  | `number of points in cluster 2` |  `double`|
| 5  | `overall silhouette` |  `double`|