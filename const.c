
/*
 * sort-test
 * 
 * Copyright (C) 2021 Dan Hare
 *
 * This file is part of sort-test, a free suite of sort algorithms
 *
 * sort-test is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * sort-test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
 
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
                                        { "Bubble Sort",            TRUE,   FALSE,  &do_bubblesort      },
                                        { "Insertion Sort",         TRUE,   FALSE,  &do_insertionsort   },
                                        { "Gnome Sort",             TRUE,   FALSE,  &do_gnomesort       },
                                        { "Quick Sort",             TRUE,   TRUE,   &do_quicksort       },
                                        { "Comb Sort",              TRUE,   TRUE,   &do_combsort        },
                                        { "Tim Sort",               TRUE,   TRUE,   &do_timsort         },
                                        { "Radix Sort (base  10)",  TRUE,   TRUE,   &do_radix10sort     },
                                        { "Radix Sort (base 256)",  TRUE,   TRUE,   &do_radix256sort    },
                                        { "Heap Sort",              TRUE,   TRUE,   &do_heapsort        },
                                        { "Cycle Sort",             TRUE,   FALSE,  &do_cyclesort       }
                                    };

const uint totalSortRuns = sizeof( sortRunPlan ) / sizeof( struct sortplan_def );
const uint totalSortAlgorithms = sizeof( sortAlgorithms ) / sizeof( struct algorithm_def );
