contract C {
	uint[] storageArray;
	function test_storage_array() public returns (uint256)
	{
		storageArray.length = 7;
		require(storageArray.length == 7);

		for (uint i = 0; i < 7; i++)
			storageArray[i] = i + 1;

		for (uint i = 0; i < 7; i++)
			require(storageArray[i] == i + 1);

		storageArray.length = 5;
		require(storageArray.length == 5);

		for (uint i = 0; i < 5; i++)
			require(storageArray[i] == i + 1);

		storageArray.length = 0;
		require(storageArray.length == 0);
		storageArray.length = 7;
		require(storageArray.length == 7);

		for (uint i = 0; i < 7; i++)
		{
			require(storageArray[i] == 0);

			uint256 val = storageArray[i];
			uint256 check;

			assembly { check := iszero(val) }

			require(check == 1);
		}

		return storageArray.length;
	}
}
// ====
// compileViaYul: true
// ----
// test_storage_array() -> 7
