// ------------------------------------------------------------------------
//
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2010 - 2024 by the deal.II authors
//
// This file is part of the deal.II library.
//
// Part of the source code is dual licensed under Apache-2.0 WITH
// LLVM-exception OR LGPL-2.1-or-later. Detailed license information
// governing the source code and code contributions can be found in
// LICENSE.md and CONTRIBUTING.md at the top level directory of deal.II.
//
// ------------------------------------------------------------------------


// test changing header style after adding entries


#include <deal.II/base/data_out_base.h>
#include <deal.II/base/table_handler.h>

#include <string>
#include <vector>

#include "../tests.h"


int
main()
{
  initlog();

  TableHandler table;
  table.set_auto_fill_mode(true);

  std::string keys[3] = {"key1", "key2", "key3"};

  // fill rows 1 and 2 partially
  table.add_value(keys[0], 0);
  table.add_value(keys[0], 1);
  // now fill row 3 completely
  table.add_value(keys[0], 2);
  table.add_value(keys[1], 123.456);
  table.add_value(keys[2], std::string("abc"));

  // now again fill row 4 partially
  table.add_value(keys[0], 1);

  // produce output. hope that row 4 is
  // completely padded
  table.write_text(deallog.get_file_stream(),
                   TableHandler::table_with_separate_column_description);

  table.set_scientific(keys[0], true);
  table.set_precision(keys[1], 1);

  table.write_text(deallog.get_file_stream(),
                   TableHandler::table_with_separate_column_description);
}
