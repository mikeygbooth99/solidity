/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Unit tests for the swarm hash computation routine.
 */

#include <libdevcore/SwarmHash.h>

#include <test/Options.h>

#include <libdevcore/Keccak256.h>

using namespace std;

namespace dev
{
namespace test
{

BOOST_AUTO_TEST_SUITE(SwarmHash)

string swarmHashHex(string const& _input)
{
	return toHex(swarmHash(_input).asBytes());
}

string bzzHashHex(bytes const& _input)
{
	return toHex(bzzHash(_input).asBytes());
}

BOOST_AUTO_TEST_CASE(test_zeros)
{
	BOOST_CHECK_EQUAL(swarmHashHex(string()), string("011b4d03dd8c01f1049143cf9c4c817e4b167f1d1b83e5c6f0f10d89ba1e7bce"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x1000 - 1, 0)), string("32f0faabc4265ac238cd945087133ce3d7e9bb2e536053a812b5373c54043adb"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x1000, 0)), string("411dd45de7246e94589ff5888362c41e85bd3e582a92d0fda8f0e90b76439bec"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x1000 + 1, 0)), string("69754a0098432bbc2e84fe1205276870748a61a065ab6ef44d6a2e7b13ce044d"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x2000 - 1, 0)), string("69ad3c581043404f775ffa8d6f1b25ad4a9ee812971190e90209c0966116a321"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x2000, 0)), string("f00222373ff82d0a178dc6271c78953e9c88f74130a52d401f5ec51475f63c43"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x2000 + 1, 0)), string("86d6773e79e02fd8145ee1aedba89ace0c15f2566db1249654000039a9a134bf"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x80000, 0)), string("cc0854fe2c6b98e920d5c14b1a88e6d4223e55b8f78883f60939aa2485e361bf"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x80020, 0)), string("ee9ffca246e70d3704740ba4df450fa6988d14a1c2439c7e734c7a77a4eb6fd3"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(0x800020, 0)), string("78b90b20c90559fb904535181a7c28929ea2f30a2329dbc25232de579709f12f"));
	BOOST_CHECK_EQUAL(swarmHashHex(string(2095104, 0)), string("a9958184589fc11b4027a4c233e777ebe2e99c66f96b74aef2a0638a94dd5439"));
}

BOOST_AUTO_TEST_CASE(bzz_hash_short)
{
	// Special case: 32 zero bytes
	BOOST_CHECK_EQUAL(bzzHashHex(bytes()), toHex(bytes(32, 0)));
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(31, 0)), "36fe2d14c5fe9ed380dc67afd9da6c5824bffcb01ac7972219c3cc3b1c8cd6b1");
	BOOST_CHECK_EQUAL(bzzHashHex(asBytes("hello world")), "92672a471f4419b255d7cb0cf313474a6f5856fb347c5ece85fb706d644b630f");
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(64, 0)), "24090f674316c306ea2a98bdd08f042d6f776d0ae1c23b27fca52750a9c7d4e5");
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(65, 0)), "6ab1eaa91095215e30cacf47131d06ce5e9fc01611e406409705e190ee4440c6");
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(4096, 0)), "09ae927d0f3aaa37324df178928d3826820f3dd3388ce4aaebfc3af410bde23a");
}

BOOST_AUTO_TEST_CASE(bzz_hash_medium)
{
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(4097, 0)), "c082943c4cb8a97c67947f290f5421cf4c61d021eb303c8df77de6fe208df516");
	BOOST_CHECK_EQUAL(bzzHashHex(bytes(4096 * 128, 0)), "392edbfc185187265cb5d50c2507965f2bb99ce8c255a24d3eb14257e40f2e33");
}

BOOST_AUTO_TEST_SUITE_END()

}
}
