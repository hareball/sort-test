#include "sort-test.h"

/* List of sort types to run */
const SORT sortRunPlan[] =  {
                                { "Small Balanced sort",            20,         0, 20,      FALSE,  ST_BALANCED     },
                                { "Medium Balanced sort",           5000,       0, 5000,    FALSE,  ST_BALANCED     },
                                { "Large Balanced sort",            50000,      0, 50000,   FALSE,  ST_BALANCED     },
                                { "Small Top Weighted sort",        20,         0, 20,      FALSE,  ST_TOP_WEIGHT   },
                                { "Medium Top Weighted sort",       5000,       0, 5000,    FALSE,  ST_TOP_WEIGHT   },
                                { "Large Top Weighted sort",        50000,      0, 50000,   FALSE,  ST_TOP_WEIGHT   },
                                { "Small Bottom Weighted sort",     20,         0, 20,      FALSE,  ST_BOT_WEIGHT   },
                                { "Medium Bottom Weighted sort",    5000,       0, 5000,    FALSE,  ST_BOT_WEIGHT   },
                                { "Large Bottom Weighted sort",     50000,      0, 50000,   FALSE,  ST_BOT_WEIGHT   },
                                { "Huge Balanced Sort",             50000000,   0, 100000,  TRUE,   ST_BALANCED     }
                            };
                            
const ALGORITHM sortAlgorithms[] =  {
                                        { "Bubble Sort",        &do_bubblesort,     FALSE   },
                                        { "Insertion Sort",     &do_insertionsort,  FALSE   },
                                        { "Gnome Sort",         &do_gnomesort,      FALSE   },
                                        { "Quick Sort",         &do_quicksort,      TRUE    },
                                        { "Comb Sort",          &do_combsort,       TRUE    },
                                        { "Tim Sort",           &do_timsort,        TRUE    },
                                        { "Radix Sort",         &do_radixsort,      TRUE    }
                                    };

const uint totalSortRuns = sizeof( sortRunPlan ) / sizeof( struct sort_ref );
const uint totalSortAlgorithms = sizeof( sortAlgorithms ) / sizeof( struct algorithm_def );
