#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "assert.h"
#include "pgcd.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE ("PGCD valeurs normales", "[pgcd]")
{
	int A;
	int B;

	SECTION(" A < B")
	{
		A = 10;
		B = 20;
		REQUIRE (A < B);
		REQUIRE (PGCD(A, B) == 10);

		A = 24;
		B = 40;
		REQUIRE (A < B);
		REQUIRE (PGCD(A, B) == 8);

		A = 1;
		B = 12;
		REQUIRE (A < B);
		REQUIRE (PGCD(A, B) == 1);
	
		A = 3;
		B = 7;
		REQUIRE (A < B);
		REQUIRE (PGCD(A, B) == 1);
	}

	SECTION(" A > B")
	{
		A = 20;
		B = 10;
		REQUIRE (A > B);
		REQUIRE (PGCD(A, B) == 10);

		A = 40;
		B = 24;
		REQUIRE (A > B);
		REQUIRE (PGCD(A, B) == 8);

		A = 12;
		B = 1;
		REQUIRE (A > B);
		REQUIRE (PGCD(A, B) == 1);
	
		A = 7;
		B = 3;
		REQUIRE (A > B);
		REQUIRE (PGCD(A, B) == 1);	
	}
	
	SECTION(" A == B")
	{
		A = 20;
		B = A;
		REQUIRE (A == B);
		REQUIRE (PGCD(A, B) == A);

		A = 40;
		B = A;
		REQUIRE (A == B);
		REQUIRE (PGCD(A, B) == A);

		A = 12;
		B = A;
		REQUIRE (A == B);
		REQUIRE (PGCD(A, B) == A);
	
		A = 7;
		B = A;
		REQUIRE (A == B);
		REQUIRE (PGCD(A, B) == A);	
	}
}


TEST_CASE("PGCD valeurs particulières", "[pgcd]")
{
	int A;
	int B;

	SECTION("A vaut 0")
	{
		A = 0;
		B = 10;
		REQUIRE (A == 0);
		REQUIRE (A != B);
		REQUIRE (PGCD(A, B) == 0);
	}

	SECTION("B vaut 0")
	{
		A = 10;
		B = 0;
		REQUIRE (B == 0);
		REQUIRE (A != B);
		REQUIRE (PGCD(A, B) == 0);
	}

	SECTION("A et B sont nuls")
	{
		A = 0;
		B = 0;
		REQUIRE (A == 0);
		REQUIRE (B == 0);
		REQUIRE (PGCD(A, B) == 0);
	}
}

