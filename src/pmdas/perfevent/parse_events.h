/*
 * Copyright (C) 2017 IBM Corp.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PARSE_EVENTS_H_
#define PARSE_EVENTS_H_

#include <linux/limits.h>
#include "architecture.h"
#include "configparser.h"

#define CONFIG  0
#define CONFIG1 1     /* Extension of config1 */
#define CONFIG2 2     /* Extension of config2 */

#define DEV_DIR "/bus/event_source/devices/"

#define EVENTS "events"
#define FORMAT "format"
#define PMU_TYPE "type"
#define PMU_CPUMASK "cpumask"

#define BUF_SIZE 1024

/*
 * Event name and configs are the things that we need for any event.
 */
struct pmu_event {
    char *name;
    unsigned long long config;
    unsigned long long config1;
    unsigned long long config2;
    double scale;
    struct pmu *pmu;                  /* Back pointer to its pmu */
    struct pmu_event *next;
};

struct property_info {
    char *name;
    unsigned long long value;
    struct property_info *next;
};

/*
 * name : name of the format property.
 * lo_bit : from where this property starts.
 * hi_bit : highest bit where the property finishes.
 */
struct property {
    char *name;
    int lo_bit;
    int hi_bit;
    int belongs_to;
    struct property *next;
};

struct pmu {
    char *name;
    int type;
    struct property *prop;
    struct pmu_event *ev;
    struct pmu *next;
};

struct software_event {
    char *name;
    unsigned long long config;
};

extern char dev_dir[];   /* Optional path prefix for the PMU devices */

extern int init_dynamic_events(struct pmu **pmu_list, struct pmcsetting *dynamicpmc);
extern void setup_cpu_config(struct pmu *pmu_ptr, int *ncpus, int **cpuarr);
extern int get_file_string(char *path, char *buf);
extern void cleanup_pmu_list(struct pmu *pmu);

#endif /* PARSE_EVENTS_H_ */
