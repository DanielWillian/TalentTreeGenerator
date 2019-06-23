#include "stdafx.h"
#include "BranchDictionary.h"

BranchDictionary::BranchDictionary()
{
	talentBranches["1A"] = {"1A", "1B", "1C", "1D", "3A"};
	talentBranches["1B"] = {"1E", "1F", "1G", "1H"};
	talentBranches["1C"] = {"1I", "1J", "1K", "1L", "3B"};
	talentBranches["1D"] = {"1M", "1N", "1O", "1P"};
	talentBranches["1E"] = {"1Q", "1R", "1S", "1T", "3C"};
	talentBranches["1F"] = {"1U", "1V", "1W", "1X"};
	talentBranches["1G"] = {"1Y", "1Z", "1a", "1b", "3D"};
	talentBranches["1H"] = {"1c", "1d", "1e", "1f"};
	talentBranches["1I"] = {"1g", "1h", "3E"};
	talentBranches["1J"] = {"1i", "1j", "1k", "1l", "3F"};
	talentBranches["1K"] = {"1m", "1n", "3G"};
	talentBranches["1L"] = {"1o", "1p", "3H"};
	talentBranches["1M"] = {"1q", "1r", "1s", "1t", "3I"};
	talentBranches["1O"] = {"1u", "1v", "3J"};
	talentBranches["1P"] = {"1w", "1x", "3K"};
	talentBranches["1Q"] = {"1y", "1z", "1AA", "1AB", "3L"};
	talentBranches["1R"] = {"1AC", "1AD", "3M"};
	talentBranches["1S"] = {"1AE", "1AF", "3N"};
	talentBranches["1T"] = {"1AG", "1AH", "1AI", "1AJ", "3O"};
	talentBranches["1U"] = {"1AK", "1AL", "3P"};

	talentBranches["2A"] = {"2A", "2B", "2C", "2D", "2E"};
	talentBranches["2B"] = {"2F", "2G", "2H", "2I", "2J"};
	talentBranches["2C"] = {"2K", "2L", "2M", "2N", "2O"};
	talentBranches["2D"] = {"2P", "2Q", "2R", "2S", "2T"};

	talentBranches["4A"] = {"4A", "4B", "4C", "4D", "6A"};
	talentBranches["4B"] = {"4E", "4F", "4G", "4H", "6B"};
	talentBranches["4C"] = {"4I", "4J", "4K", "4L", "6C"};
	talentBranches["4D"] = {"4M", "4N", "4O", "4P", "6D"};
	talentBranches["4E"] = {"4Q", "4R", "4S", "4T", "6E"};
	talentBranches["4F"] = {"4U", "4V", "4W", "4X", "6F"};
	talentBranches["4G"] = {"4Y", "4Z", "4a", "4b", "6G"};
	talentBranches["4H"] = {"4c", "4d", "4e", "4f", "6H"};
	talentBranches["4I"] = {"4g", "4h", "4i", "4j", "6I"};
	talentBranches["4J"] = {"4k", "4l", "4m", "4n", "6J"};
	talentBranches["4K"] = {"4o", "4p", "4q", "4r", "6K"};
	talentBranches["4L"] = {"4s", "4t", "4u", "4v", "6L"};
	talentBranches["4M"] = {"4w", "4x", "4y", "4z", "6M"};
	talentBranches["4N"] = {"4AA", "4AB", "4AC", "4AD", "6N"};
	talentBranches["4O"] = {"4AE", "4AF", "4AG", "4AH", "6O"};
	talentBranches["4P"] = {"4AI", "4AJ", "4AK", "4AL", "6P"};

	talentBranches["4Q"] = {"4AM", "4AN", "4AO", "4AP", "6Q"};
	talentBranches["4R"] = {"4AQ", "4AR", "4AS", "4AT", "6R"};
	talentBranches["4S"] = {"4AU", "4AV", "4AW", "4AX", "6S"};
	talentBranches["4T"] = {"4AY", "4AZ", "4Aa", "4Ab", "6T"};
	talentBranches["4U"] = {"4Ac", "4Ad", "4Ae", "4Af", "6U"};
	talentBranches["4V"] = {"4Ag", "4Ah", "4Ai", "4Aj", "6V"};
	talentBranches["4W"] = {"4Ak", "4Al", "4Am", "4An", "6W"};
	talentBranches["4X"] = {"4Ao", "4Ap", "4Aq", "4Ar", "6X"};
	talentBranches["4Y"] = {"4As", "4At", "4Au", "4Av", "6Y"};
	talentBranches["4Z"] = {"4Aw", "4Ax", "4Ay", "4Az", "6Z"};
	talentBranches["4a"] = {"4BA", "4BB", "4BC", "4BD", "6a"};
	talentBranches["4b"] = {"4BE", "4BF", "4BG", "4BH", "6b"};
	talentBranches["4c"] = {"4BI", "4BJ", "4BK", "4BL", "6c"};
	talentBranches["4d"] = {"4BM", "4BN", "4BO", "4BP", "6d"};
	talentBranches["4e"] = {"4BQ", "4BR", "4BS", "4BT", "6e"};
	talentBranches["4f"] = {"4BU", "4BV", "4BW", "4BX", "6f"};

	talentBranches["4g"] = {"4BY", "4BZ", "4Ba", "6g"};
	talentBranches["4h"] = {"4Bb", "4Bc", "4Bd", "4Be", "4Bf", "6h"};
	talentBranches["4i"] = {"4Bg", "4Bh", "4Bi", "4Bj", "4Bk", "6i"};
	talentBranches["4j"] = {"4Bl", "4Bm", "4Bn", "6j"};
	talentBranches["4k"] = {"4Bo", "4Bp", "4Bq", "6k"};
	talentBranches["4l"] = {"4Br", "4Bs", "4Bt", "4Bu", "4Bv", "6l"};
	talentBranches["4m"] = {"4Bw", "4Bx", "4By", "4Bz", "4CA", "6m"};
	talentBranches["4n"] = {"4CB", "4CC", "4CD", "6n"};
	talentBranches["4o"] = {"4CE", "4CF", "4CG", "6o"};
	talentBranches["4p"] = {"4CH", "4CI", "4CJ", "4CK", "4CL", "6p"};
	talentBranches["4q"] = {"4CM", "4CN", "4CO", "4CP", "4CQ", "6q"};
	talentBranches["4r"] = {"4CR", "4CS", "4CT", "6r"};
	talentBranches["4s"] = {"4CU", "4CV", "4CW", "6s"};
	talentBranches["4t"] = {"4CX", "4CY", "4CZ", "4Ca", "4Cb", "6t"};
	talentBranches["4u"] = {"4Cc", "4Cd", "4Ce", "4Cf", "4Cg", "6u"};
	talentBranches["4v"] = {"4Ch", "4Ci", "4Cj", "6v"};
	talentBranches["4w"] = {"4Ck", "4Cl", "4Cm", "6w"};
	talentBranches["4x"] = {"4Cn", "4Co", "4Cp", "4Cq", "4Cr", "6x"};
	talentBranches["4y"] = {"4Cs", "4Ct", "4Cu", "4Cv", "4Cw", "6y"};
	talentBranches["4z"] = {"4Cx", "4Cy", "4Cz", "6z"};
	talentBranches["4AA"] = {"4DA", "4DB", "4DC", "6AA"};
	talentBranches["4AB"] = {"4DD", "4DE", "4DF", "4DG", "4DH", "6AB"};
	talentBranches["4AC"] = {"4DI", "4DJ", "4DK", "4DL", "4DM", "6AC"};
	talentBranches["4AD"] = {"4DN", "4DO", "4DP", "6AD"};
	talentBranches["4AE"] = {"4DQ", "4DR", "4DS", "6AE"};
	talentBranches["4AF"] = {"4DT", "4DU", "4DV", "4DW", "4DX", "6AF"};
	talentBranches["4AG"] = {"4DY", "4DZ", "4Da", "4Db", "4Dc", "6AG"};
	talentBranches["4AH"] = {"4Dd", "4De", "4Df", "6AH"};
	talentBranches["4AI"] = {"4Dg", "4Dh", "4Di", "6AI"};
	talentBranches["4AJ"] = {"4Dj", "4Dk", "4Dl", "4Dm", "4Dn", "6AJ"};
	talentBranches["4AK"] = {"4Do", "4Dp", "4Dq", "4Dr", "4Ds", "6AK"};
	talentBranches["4AL"] = {"4Dt", "4Du", "4Dv", "6AL"};

	talentBranches["5A"] = {"5A", "5B", "5C", "5D", "5E", "5F", "5G"};
	talentBranches["5B"] = {"5H", "5I", "5J", "5K", "5L", "5M", "5N"};
	talentBranches["5C"] = {"5O", "5P", "5Q", "5R", "5S", "5T", "5U"};
	talentBranches["5D"] = {"5V", "5W", "5X", "5Y", "5Z", "5a", "5b"};
	talentBranches["5E"] = {"5c", "5d", "5e", "5f", "5g", "5h", "5i"};
	talentBranches["5F"] = {"5j", "5k", "5l", "5m", "5n", "5o", "5p"};
	talentBranches["5G"] = {"5q", "5r", "5s", "5t", "5u", "5v", "5w"};
	talentBranches["5H"] = {"5x", "5y", "5z", "5AA", "5AB", "5AC", "5AD"};

	talentBranches["7A"] = {"7A", "7B", "7C", "7D", "7E", "7F", "7G", "8A", "8B"};
	talentBranches["7B"] = {"7H", "7I", "7J", "7K", "7L", "7M", "7N", "8C", "8D"};
	talentBranches["7C"] = {"7O", "7P", "7Q", "7R", "7S", "7T", "7U", "8E", "8F"};
	talentBranches["7D"] = {"7V", "7W", "7X", "7Y", "7Z", "7a", "7b", "8G", "8H"};
	talentBranches["7E"] = {"7c", "7d", "7e", "7f", "7g", "7h", "7i", "8I", "8J"};
	talentBranches["7F"] = {"7j", "7k", "7l", "7m", "7n", "7o", "7p", "8K", "8L"};
	talentBranches["7G"] = {"7q", "7r", "7s", "7t", "7u", "7v", "7w", "8M", "8N"};
	talentBranches["7H"] = {"7x", "7y", "7z", "7AA", "7AB", "7AC", "7AD", "8O", "8P"};
	talentBranches["7I"] = {"7AE", "7AF", "7AG", "7AH", "7AI", "7AJ", "7AK", "8Q", "8R"};
	talentBranches["7J"] = {"7AL", "7AM", "7AN", "7AO", "7AP", "7AQ", "7AR", "8S", "8T"};
	talentBranches["7K"] = {"7AS", "7AT", "7AU", "7AV", "7AW", "7AX", "7AY", "8U", "8V"};
	talentBranches["7L"] = {"7AZ", "7Aa", "7Ab", "7Ac", "7Ad", "7Ae", "7Af", "8W", "8X"};
	talentBranches["7M"] = {"7Ag", "7Ah", "7Ai", "7Aj", "7Ak", "7Al", "7Am", "8Y", "8Z"};
	talentBranches["7N"] = {"7An", "7Ao", "7Ap", "7Aq", "7Ar", "7As", "7At", "8a", "8b"};
	talentBranches["7O"] = {"7Au", "7Av", "7Aw", "7Ax", "7Ay", "7Az", "7BA", "8c", "8d"};
	talentBranches["7P"] = {"7BB", "7BC", "7BD", "7BE", "7BF", "7BG", "7BH", "8e", "8f"};

	talentBranches["9A"] = {"9A"};
	talentBranches["9B"] = {"9B"};
	talentBranches["9C"] = {"9C"};
	talentBranches["9D"] = {"9D"};
	talentBranches["9E"] = {"9E"};
	talentBranches["9F"] = {"9F"};
	talentBranches["9G"] = {"9G"};
	talentBranches["9H"] = {"9H"};
}

