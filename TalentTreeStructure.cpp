#include "stdafx.h"
#include "TalentTreeStructure.h"

TalentTreeStructure::TalentTreeStructure()
{
	talentPaths["1A"] = {"1A", "1B", "1C", "1D", "3A"};
	talentPaths["1B"] = {"1E", "1F", "1G", "1H"};
	talentPaths["1C"] = {"1I", "1J", "1K", "1L", "3B"};
	talentPaths["1D"] = {"1M", "1N", "1O", "1P"};
	talentPaths["1E"] = {"1Q", "1R", "1S", "1T", "3C"};
	talentPaths["1F"] = {"1U", "1V", "1W", "1X"};
	talentPaths["1G"] = {"1Y", "1Z", "1a", "1b", "3D"};
	talentPaths["1H"] = {"1c", "1d", "1e", "1f"};
	talentPaths["1I"] = {"1g", "1h", "3E"};
	talentPaths["1J"] = {"1i", "1j", "1k", "1l", "3F"};
	talentPaths["1K"] = {"1m", "1n", "3G"};
	talentPaths["1L"] = {"1o", "1p", "3H"};
	talentPaths["1M"] = {"1q", "1r", "1s", "1t", "3I"};
	talentPaths["1O"] = {"1u", "1v", "3J"};
	talentPaths["1P"] = {"1w", "1x", "3K"};
	talentPaths["1Q"] = {"1y", "1z", "1AA", "1AB", "3L"};
	talentPaths["1R"] = {"1AC", "1AD", "3M"};
	talentPaths["1S"] = {"1AE", "1AF", "3N"};
	talentPaths["1T"] = {"1AG", "1AH", "1AI", "1AJ", "3O"};
	talentPaths["1U"] = {"1AK", "1AL", "3P"};

	talentPaths["2A"] = {"2A", "2B", "2C", "2D", "2E"};
	talentPaths["2B"] = {"2F", "2G", "2H", "2I", "2J"};
	talentPaths["2C"] = {"2K", "2L", "2M", "2N", "2O"};
	talentPaths["2D"] = {"2P", "2Q", "2R", "2S", "2T"};

	talentPaths["4A"] = {"4A", "4B", "4C", "4D", "6A"};
	talentPaths["4B"] = {"4E", "4F", "4G", "4H", "6B"};
	talentPaths["4C"] = {"4I", "4J", "4K", "4L", "6C"};
	talentPaths["4D"] = {"4M", "4N", "4O", "4P", "6D"};
	talentPaths["4E"] = {"4Q", "4R", "4S", "4T", "6E"};
	talentPaths["4F"] = {"4U", "4V", "4W", "4X", "6F"};
	talentPaths["4G"] = {"4Y", "4Z", "4a", "4b", "6G"};
	talentPaths["4H"] = {"4c", "4d", "4e", "4f", "6H"};
	talentPaths["4I"] = {"4g", "4h", "4i", "4j", "6I"};
	talentPaths["4J"] = {"4k", "4l", "4m", "4n", "6J"};
	talentPaths["4K"] = {"4o", "4p", "4q", "4r", "6K"};
	talentPaths["4L"] = {"4s", "4t", "4u", "4v", "6L"};
	talentPaths["4M"] = {"4w", "4x", "4y", "4z", "6M"};
	talentPaths["4N"] = {"4AA", "4AB", "4AC", "4AD", "6N"};
	talentPaths["4O"] = {"4AE", "4AF", "4AG", "4AH", "6O"};
	talentPaths["4P"] = {"4AI", "4AJ", "4AK", "4AL", "6P"};

	talentPaths["4Q"] = {"4AM", "4AN", "4AO", "4AP", "6Q"};
	talentPaths["4R"] = {"4AQ", "4AR", "4AS", "4AT", "6R"};
	talentPaths["4S"] = {"4AU", "4AV", "4AW", "4AX", "6S"};
	talentPaths["4T"] = {"4AY", "4AZ", "4Aa", "4Ab", "6T"};
	talentPaths["4U"] = {"4Ac", "4Ad", "4Ae", "4Af", "6U"};
	talentPaths["4V"] = {"4Ag", "4Ah", "4Ai", "4Aj", "6V"};
	talentPaths["4W"] = {"4Ak", "4Al", "4Am", "4An", "6W"};
	talentPaths["4X"] = {"4Ao", "4Ap", "4Aq", "4Ar", "6X"};
	talentPaths["4Y"] = {"4As", "4At", "4Au", "4Av", "6Y"};
	talentPaths["4Z"] = {"4Aw", "4Ax", "4Ay", "4Az", "6Z"};
	talentPaths["4a"] = {"4BA", "4BB", "4BC", "4BD", "6a"};
	talentPaths["4b"] = {"4BE", "4BF", "4BG", "4BH", "6b"};
	talentPaths["4c"] = {"4BI", "4BJ", "4BK", "4BL", "6c"};
	talentPaths["4d"] = {"4BM", "4BN", "4BO", "4BP", "6d"};
	talentPaths["4e"] = {"4BQ", "4BR", "4BS", "4BT", "6e"};
	talentPaths["4f"] = {"4BU", "4BV", "4BW", "4BX", "6f"};

	talentPaths["4g"] = {"4BY", "4BZ", "4Ba", "6g"};
	talentPaths["4h"] = {"4Bb", "4Bc", "4Bd", "4Be", "4Bf", "6h"};
	talentPaths["4i"] = {"4Bg", "4Bh", "4Bi", "4Bj", "4Bk", "6i"};
	talentPaths["4j"] = {"4Bl", "4Bm", "4Bn", "6j"};
	talentPaths["4k"] = {"4Bo", "4Bp", "4Bq", "6k"};
	talentPaths["4l"] = {"4Br", "4Bs", "4Bt", "4Bu", "4Bv", "6l"};
	talentPaths["4m"] = {"4Bw", "4Bx", "4By", "4Bz", "4CA", "6m"};
	talentPaths["4n"] = {"4CB", "4CC", "4CD", "6n"};
	talentPaths["4o"] = {"4CE", "4CF", "4CG", "6o"};
	talentPaths["4p"] = {"4CH", "4CI", "4CJ", "4CK", "4CL", "6p"};
	talentPaths["4q"] = {"4CM", "4CN", "4CO", "4CP", "4CQ", "6q"};
	talentPaths["4r"] = {"4CR", "4CS", "4CT", "6r"};
	talentPaths["4s"] = {"4CU", "4CV", "4CW", "6s"};
	talentPaths["4t"] = {"4CX", "4CY", "4CZ", "4Ca", "4Cb", "6t"};
	talentPaths["4u"] = {"4Cc", "4Cd", "4Ce", "4Cf", "4Cg", "6u"};
	talentPaths["4v"] = {"4Ch", "4Ci", "4Cj", "6v"};
	talentPaths["4w"] = {"4Ck", "4Cl", "4Cm", "6w"};
	talentPaths["4x"] = {"4Cn", "4Co", "4Cp", "4Cq", "4Cr", "6x"};
	talentPaths["4y"] = {"4Cs", "4Ct", "4Cu", "4Cv", "4Cw", "6y"};
	talentPaths["4z"] = {"4Cx", "4Cy", "4Cz", "6z"};
	talentPaths["4AA"] = {"4DA", "4DB", "4DC", "6AA"};
	talentPaths["4AB"] = {"4DD", "4DE", "4DF", "4DG", "4DH", "6AB"};
	talentPaths["4AC"] = {"4DI", "4DJ", "4DK", "4DL", "4DM", "6AC"};
	talentPaths["4AD"] = {"4DN", "4DO", "4DP", "6AD"};
	talentPaths["4AE"] = {"4DQ", "4DR", "4DS", "6AE"};
	talentPaths["4AF"] = {"4DT", "4DU", "4DV", "4DW", "4DX", "6AF"};
	talentPaths["4AG"] = {"4DY", "4DZ", "4Da", "4Db", "4Dc", "6AG"};
	talentPaths["4AH"] = {"4Dd", "4De", "4Df", "6AH"};
	talentPaths["4AI"] = {"4Dg", "4Dh", "4Di", "6AI"};
	talentPaths["4AJ"] = {"4Dj", "4Dk", "4Dl", "4Dm", "4Dn", "6AJ"};
	talentPaths["4AK"] = {"4Do", "4Dp", "4Dq", "4Dr", "4Ds", "6AK"};
	talentPaths["4AL"] = {"4Dt", "4Du", "4Dv", "6AL"};

	talentPaths["5A"] = {"5A", "5B", "5C", "5D", "5E", "5F", "5G"};
	talentPaths["5B"] = {"5H", "5I", "5J", "5K", "5L", "5M", "5N"};
	talentPaths["5C"] = {"5O", "5P", "5Q", "5R", "5S", "5T", "5U"};
	talentPaths["5D"] = {"5V", "5W", "5X", "5Y", "5Z", "5a", "5b"};
	talentPaths["5E"] = {"5c", "5d", "5e", "5f", "5g", "5h", "5i"};
	talentPaths["5F"] = {"5j", "5k", "5l", "5m", "5n", "5o", "5p"};
	talentPaths["5G"] = {"5q", "5r", "5s", "5t", "5u", "5v", "5w"};
	talentPaths["5H"] = {"5x", "5y", "5z", "5AA", "5AB", "5AC", "5AD"};

	talentPaths["7A"] = {"7A", "7B", "7C", "7D", "7E", "7F", "7G", "8A", "8B"};
	talentPaths["7B"] = {"7H", "7I", "7J", "7K", "7L", "7M", "7N", "8C", "8D"};
	talentPaths["7C"] = {"7O", "7P", "7Q", "7R", "7S", "7T", "7U", "8E", "8F"};
	talentPaths["7D"] = {"7V", "7W", "7X", "7Y", "7Z", "7a", "7b", "8G", "8H"};
	talentPaths["7E"] = {"7c", "7d", "7e", "7f", "7g", "7h", "7i", "8I", "8J"};
	talentPaths["7F"] = {"7j", "7k", "7l", "7m", "7n", "7o", "7p", "8K", "8L"};
	talentPaths["7G"] = {"7q", "7r", "7s", "7t", "7u", "7v", "7w", "8M", "8N"};
	talentPaths["7H"] = {"7x", "7y", "7z", "7AA", "7AB", "7AC", "7AD", "8O", "8P"};
	talentPaths["7I"] = {"7AE", "7AF", "7AG", "7AH", "7AI", "7AJ", "7AK", "8Q", "8R"};
	talentPaths["7J"] = {"7AL", "7AM", "7AN", "7AO", "7AP", "7AQ", "7AR", "8S", "8T"};
	talentPaths["7K"] = {"7AS", "7AT", "7AU", "7AV", "7AW", "7AX", "7AY", "8U", "8V"};
	talentPaths["7L"] = {"7AZ", "7Aa", "7Ab", "7Ac", "7Ad", "7Ae", "7Af", "8W", "8X"};
	talentPaths["7M"] = {"7Ag", "7Ah", "7Ai", "7Aj", "7Ak", "7Al", "7Am", "8Y", "8Z"};
	talentPaths["7N"] = {"7An", "7Ao", "7Ap", "7Aq", "7Ar", "7As", "7At", "8a", "8b"};
	talentPaths["7O"] = {"7Au", "7Av", "7Aw", "7Ax", "7Ay", "7Az", "7BA", "8c", "8d"};
	talentPaths["7P"] = {"7BB", "7BC", "7BD", "7BE", "7BF", "7BG", "7BH", "8e", "8f"};

	talentPaths["9A"] = {"9A"};
	talentPaths["9B"] = {"9B"};
	talentPaths["9C"] = {"9C"};
	talentPaths["9D"] = {"9D"};
	talentPaths["9E"] = {"9E"};
	talentPaths["9F"] = {"9F"};
	talentPaths["9G"] = {"9G"};
	talentPaths["9H"] = {"9H"};
}

