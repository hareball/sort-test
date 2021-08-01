#include "sort-test.h"

/* List of sort types to run */
const SORT sortRunPlan[] =  {
                                { "Small Balanced sort",            20,         0, 20,      TRUE,   FALSE, ST_BALANCED     },
                                { "Medium Balanced sort",           5000,       0, 5000,    TRUE,   FALSE, ST_BALANCED     },
                                { "Large Balanced sort",            50000,      0, 50000,   TRUE,   FALSE, ST_BALANCED     },
                                { "Small Top Weighted sort",        20,         0, 20,      TRUE,   FALSE, ST_TOP_WEIGHT   },
                                { "Medium Top Weighted sort",       5000,       0, 5000,    TRUE,   FALSE, ST_TOP_WEIGHT   },
                                { "Large Top Weighted sort",        50000,      0, 50000,   TRUE,   FALSE, ST_TOP_WEIGHT   },
                                { "Small Bottom Weighted sort",     20,         0, 20,      TRUE,   FALSE, ST_BOT_WEIGHT   },
                                { "Medium Bottom Weighted sort",    5000,       0, 5000,    TRUE,   FALSE, ST_BOT_WEIGHT   },
                                { "Large Bottom Weighted sort",     50000,      0, 50000,   TRUE,   FALSE, ST_BOT_WEIGHT   },
                                { "Huge Balanced Sort",             50000000,   0, 100000,  TRUE,   TRUE,  ST_BALANCED     }
                            };
                            
const ALGORITHM sortAlgorithms[] =  {
                                        { "Bubble Sort",    TRUE,   FALSE,  &do_bubblesort      },
                                        { "Insertion Sort", TRUE,   FALSE,  &do_insertionsort   },
                                        { "Gnome Sort",     TRUE,   FALSE,  &do_gnomesort       },
                                        { "Quick Sort",     TRUE,   TRUE,   &do_quicksort       },
                                        { "Comb Sort",      TRUE,   TRUE,   &do_combsort        },
                                        { "Tim Sort",       TRUE,   TRUE,   &do_timsort         },
                                        { "Radix Sort",     TRUE,   TRUE,   &do_radixsort       }
                                    };

const uint totalSortRuns = sizeof( sortRunPlan ) / sizeof( struct sortplan_def );
const uint totalSortAlgorithms = sizeof( sortAlgorithms ) / sizeof( struct algorithm_def );
