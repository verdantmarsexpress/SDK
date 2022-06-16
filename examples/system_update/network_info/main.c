// Copyright (c) 2022, Myriota Pty Ltd, All Rights Reserved
// SPDX-License-Identifier: BSD-3-Clause-Attribution
//
// This file is licensed under the BSD with attribution  (the "License"); you
// may not use these files except in compliance with the License.
//
// You may obtain a copy of the License here:
// LICENSE-BSD-3-Clause-Attribution.txt and at
// https://spdx.org/licenses/BSD-3-Clause-Attribution.html
//
// See the License for the specific language governing permissions and
// limitations under the License.

// This example demonstrates network information update via system update APIs.

#include <string.h>
#include "myriota_user_api.h"
#include "network_info_example.h"

#define MAX_WRITE 128
static uint32_t bytes_written = 0;

static int restart_update(void) {
  printf("INFO: Restarting network info update restarted\n");

  bytes_written = 0;
  SystemUpdateFinish();
  return SystemUpdateStart(SYSTEM_UPDATE_ID_NETWORK, NETWORK_INFO_EXAMPLE_len,
                           20);
}

static int NetworkInfoStart(void) {
  return SystemUpdateStart(SYSTEM_UPDATE_ID_NETWORK, NETWORK_INFO_EXAMPLE_len,
                           20);
}

static int NetworkInfoUpdateXfer(void) {
  uint32_t bytes_this_write = NETWORK_INFO_EXAMPLE_len - bytes_written;
  if (bytes_this_write >= MAX_WRITE) bytes_this_write = MAX_WRITE;

  int ret = SystemUpdateXfer(
      bytes_written, NETWORK_INFO_EXAMPLE + bytes_written, bytes_this_write);

  printf("NetworkInfo bytes transfer %s\n", ret ? "failed" : "succeeded");

  if (ret == 0) bytes_written += bytes_this_write;
  return 0;
}

static int NetworkInfoUpdateFinalise(void) {
  int ret = SystemUpdateFinish();
  printf("NetworkInfo update %s\n", ret ? "failed" : "succeeded");

  return ret;
}

static time_t NetworkInfoUpdateTask(void) {
  int ret = NetworkInfoStart();
  if (ret != 0) {
    printf("*** Error starting network info update: ret %d\n", ret);
    return SecondsFromNow(5);
  }

  printf("Network info update started\n");
  while (true) {
    if (bytes_written < NETWORK_INFO_EXAMPLE_len) ret = NetworkInfoUpdateXfer();

    if (ret == 0 && bytes_written >= NETWORK_INFO_EXAMPLE_len) {
      ret = NetworkInfoUpdateFinalise();
      if (ret == 0) break;
    }

    if (ret) ret = restart_update();
  }

  return Never();
}

void AppInit() { ScheduleJob(NetworkInfoUpdateTask, SecondsFromNow(5)); }
