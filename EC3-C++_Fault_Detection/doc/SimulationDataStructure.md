# Simulation Memory

Simulation Memory corresponds to a folder in "\data" directory and it stores:

- relevant output logs from the simulation history;
- the list of all components that can interfere with the occurrence of critical faults in the supervised system;
- the failure parameters related to the listed components (failure rate, failure modes, etc).


The data structure adopted in each of the files found in Simulation Memory is described below.

## *HistoricalFailureLog.csv*'s structure

**Separator Character:** "," (comma)

| Column Position  | Meaning | Data Type |
| ------------- | ------------- | ------------- |
| 0  | `iteration`  | `integer`|
| 1  | `metric that reported the failure`  |  `enum metrics` |
| 2  | `tolerance adopted for the metric variation` |  `double`|
| 3  | `variation of the metric value` |  `double`|

`enum metrics` is an enumerator type that represents the clustering metrics used by supervisor system

1. `silhouetteCluster1` refers to the silhouette score of cluster 1
2. `silhouetteCluster2` refers to silhouette score of cluster 2
3. `numPointsCluster1` refers to the number of points in cluster 1
4. `numPointsCluster2` refers to the number of points in cluster 2
5. `overallSilhouette` refers to the overall silhouette score
6. `imbalanceNumPoints` refers to the difference between the amount of points from each cluster

## *ComponentsFailureSpecs.csv*'s structure

**Separator Character:** "," (comma)

| Column Position  | Meaning | Data Type |
| ------------- | ------------- | ------------- |
| 0  | `component name`  | `enum components`|
| 1  | `failure rate ($s^{-1}$)`  |  `double` |
| 2  | `countBetweenFailures` |  `double` |