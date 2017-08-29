/*
 * Copyright (c) 2013-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <inttypes.h>
#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "main-hw.h"

/* Declaring a function to be used as halt_error function for the debug box. */
static void example_halt_error(THaltError reason, const THaltInfo *halt_info);

/* Create ACLs for main box. */
MAIN_ACL(g_main_acl);

/* Enable uVisor. */
UVISOR_SET_MODE_ACL(UVISOR_ENABLED, g_main_acl);
UVISOR_SET_PAGE_HEAP(8 * 1024, 5);

/* Create a valid debug driver struct and use example_halt_error() as its halt_error() function */
UVISOR_PUBLIC_BOX_DEBUG_DRIVER(example_halt_error);

/* Targets with an ARMv7-M MPU needs this space adjustment to prevent a runtime
 * memory overflow error. The code below has been output directly by uVisor. */
#if defined(TARGET_EFM32GG_STK3700) || defined(TARGET_DISCO_F429ZI)
uint8_t __attribute__((section(".keep.uvisor.bss.boxes"), aligned(32))) __boxes_overhead[8064];
#endif

static void example_halt_error(THaltError reason, const THaltInfo *halt_info)
{
    const char *exception_stack[] = {"R0", "R1", "R2", "R3", "R12", "LR", "PC", "xPSR"};
    printf("***** uVisor debug box example *****\r\n");
    printf("Failed with an error code: 0x%08" PRIx32 "\r\n\r\n", (uint32_t)reason);

    if (halt_info == NULL) {
        return;
    }

    if ((halt_info->valid_data & HALT_INFO_STACK_FRAME)) {
        printf("Exception stack frame:\r\n");
        for (int i = sizeof(exception_stack) / sizeof(exception_stack[0]) - 1; i >= 0; i--) {
            printf("SP[%02d]: 0x%08" PRIx32 " | %s\r\n", i, ((uint32_t *)&halt_info->stack_frame)[i], exception_stack[i]);
        }

        printf("\r\n");
    }

    if ((halt_info->valid_data & HALT_INFO_REGISTERS)) {
        printf("Registers after fault:\r\n");
        printf("LR:      0x%08" PRIx32 "\r\n", halt_info->lr);
        printf("IPSR:    0x%08" PRIx32 "\r\n", halt_info->ipsr);
        printf("CONTROL: 0x%08" PRIx32 "\r\n", halt_info->control);
        printf("\r\n");

        printf("Fault registers:\r\n");
        printf("CFSR:  0x%08" PRIx32 "\r\n", halt_info->cfsr);
        printf("HFSR:  0x%08" PRIx32 "\r\n", halt_info->hfsr);
        printf("DFSR:  0x%08" PRIx32 "\r\n", halt_info->dfsr);
        printf("AFSR:  0x%08" PRIx32 "\r\n", halt_info->afsr);
        if (halt_info->cfsr & SCB_CFSR_MMARVALID_Msk) {
            printf("MMFAR: 0x%08" PRIx32 "\r\n", halt_info->mmfar);
        } else {
            printf("MMFAR: Invalid\r\n");
        }

        if (halt_info->cfsr & SCB_CFSR_BFARVALID_Msk) {
            printf("BFAR:  0x%08" PRIx32 "\r\n", halt_info->bfar);
        } else {
            printf("BFAR:  Invalid\r\n");
        }

        printf("\r\n");
    }
}

#define BAD_BAD_ADDR (*((volatile unsigned long *) (0xFFFFFFFF)))

int main(void)
{
    while (1){
        BAD_BAD_ADDR = 13;
    }

    return 0;
}
