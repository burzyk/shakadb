/*
 * Copyright (c) 2016 Pawel Burzynski. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
//
// Created by Pawel Burzynski on 29/01/2017.
//

#include "test/tests/rw-lock-tests.h"

#include "src/utils/rw-lock.h"

namespace shakadb {
namespace test {

void RwLockTests::double_read_lock_test(TestContext ctx) {
  RwLock lock;

  auto s1 = lock.LockRead();
  auto s2 = lock.LockRead();
}

void RwLockTests::upgrade_lock_test(TestContext ctx) {
  RwLock lock;

  auto s1 = lock.LockRead();
  s1->UpgradeToWrite();
}

void RwLockTests::release_and_lock_again_test(TestContext ctx) {
  RwLock lock;

  auto s1 = lock.LockRead();

  // Scope
  {
    auto s2 = lock.LockRead();
  }

  s1->UpgradeToWrite();
}

}  // namespace test
}  // namespace shakadb