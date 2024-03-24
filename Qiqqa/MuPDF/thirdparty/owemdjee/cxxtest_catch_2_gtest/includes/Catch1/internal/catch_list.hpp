/*
 *  Created by Phil on 5/11/2010.
 *  Copyright 2010 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_LIST_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_LIST_HPP_INCLUDED

#include "catch_commandline.hpp"
#include "catch_text.h"
#include "catch_console_colour.hpp"
#include "catch_interfaces_reporter.h"
#include "catch_test_spec_parser.hpp"

#include <limits>
#include <algorithm>

namespace Catch {

	std::size_t listTests(Config const& config);

	std::size_t listTestsNamesOnly(Config const& config);

    struct TagInfo {
        TagInfo() : count ( 0 ) {}
        void add( std::string const& spelling ) {
            ++count;
            spellings.insert( spelling );
        }
        std::string all() const {
            std::string out;
            for( std::set<std::string>::const_iterator it = spellings.begin(), itEnd = spellings.end();
                        it != itEnd;
                        ++it )
                out += "[" + *it + "]";
            return out;
        }
        std::set<std::string> spellings;
        std::size_t count;
    };

	std::size_t listTags(Config const& config);

	std::size_t listReporters(Config const& /*config*/);

	Option<std::size_t> list(Config const& config);

} // end namespace Catch

#endif // TWOBLUECUBES_CATCH_LIST_HPP_INCLUDED
