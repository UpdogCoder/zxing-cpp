/*
* Copyright 2016 ZXing authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "oned/ODUPCEANExtensionSupport.h"
#include "oned/ODUPCEANReader.h"
#include "Result.h"

namespace ZXing {

namespace OneD {

static const std::array<int, 3> EXTENSION_START_PATTERN = { 1,1,2 };

Result
UPCEANExtensionSupport::DecodeRow(int rowNumber, const BitArray& row, int rowOffset)
{
	int extStartRangeBegin, extStartRangeEnd;
	auto status = UPCEANReader::FindGuardPattern(row, rowOffset, false, EXTENSION_START_PATTERN, extStartRangeBegin, extStartRangeEnd);
	if (StatusIsError(status))
		return Result(status);
	try {
		return fiveSupport.decodeRow(rowNumber, row, extensionStartRange);
	}
	catch (ReaderException ignored) {
		return twoSupport.decodeRow(rowNumber, row, extensionStartRange);
	}
}

} // OneD
} // ZXing
