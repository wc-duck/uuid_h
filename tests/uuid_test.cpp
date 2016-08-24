/*
    Single-file, STB-style, library to generate UUID:s. No dependencies
    except for OS-provided functionality.

    version 0.1, August, 2016

    Copyright (C) 2016- Fredrik Kihlander

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Fredrik Kihlander
*/

#define UUID_IMPLEMENTATION
#include "../uuid.h"
#include "greatest.h"

TEST uuid_twice()
{
	uuid id1;
	uuid id2;
	uuid4_generate( &id1 );
	uuid4_generate( &id2 );
	ASSERT( memcmp( id1.bytes, id2.bytes, sizeof( uuid ) ) != 0 );
	return 0;
}

TEST uuid_is_version_4()
{
	for( int i = 0; i < 100; ++i )
	{
		uuid id;
		uuid4_generate( &id );
		ASSERT_EQ( 4, uuid_type( &id ) );
	}
	return 0;
}

TEST uuid_roundabout()
{
	uuid id;
	uuid4_generate( &id );

	ASSERT_EQ( 4, uuid_type( &id ) );
	char uuid_str[37] = {0};

	ASSERT( uuid_to_string( &id, uuid_str ) );
	ASSERT_EQ( '-', uuid_str[8] );
	ASSERT_EQ( '-', uuid_str[13] );
	ASSERT_EQ( '-', uuid_str[18] );
	ASSERT_EQ( '-', uuid_str[23] );

	uuid parsed;
	uuid_from_string( uuid_str, &parsed );

	ASSERT_EQ( 0, memcmp( &id, &parsed, sizeof( uuid ) ) );
	return 0;
}

TEST uuid_to_from_null_str()
{
	char null_uuid[37] = "00000000-0000-0000-0000-000000000000";
	uuid id;
	uuid_from_string( null_uuid, &id );
	ASSERT_EQ( 0, uuid_type( &id ) );
	return 0;
}

TEST uuid_from_string()
{
	char null_uuid[37] = "01234867-89ab-cdef-0123-456789abcdef";
	uuid id;
	uuid_from_string( null_uuid, &id );
	unsigned char expected[16] = { 0x01, 0x23, 0x48, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
	ASSERT_EQ( expected[0], id.bytes[0] );
	ASSERT_EQ( expected[1], id.bytes[1] );
	ASSERT_EQ( expected[2], id.bytes[2] );
	ASSERT_EQ( expected[3], id.bytes[3] );
	ASSERT_EQ( expected[4], id.bytes[4] );
	ASSERT_EQ( expected[5], id.bytes[5] );
	ASSERT_EQ( expected[6], id.bytes[6] );
	ASSERT_EQ( expected[7], id.bytes[7] );
	ASSERT_EQ( expected[8], id.bytes[8] );
	ASSERT_EQ( expected[9], id.bytes[9] );
	ASSERT_EQ( expected[10], id.bytes[10] );
	ASSERT_EQ( expected[11], id.bytes[11] );
	ASSERT_EQ( expected[12], id.bytes[12] );
	ASSERT_EQ( expected[13], id.bytes[13] );
	ASSERT_EQ( expected[14], id.bytes[14] );
	ASSERT_EQ( expected[15], id.bytes[15] );
	return 0;
}

GREATEST_SUITE( uuid )
{
        RUN_TEST( uuid_twice );
        RUN_TEST( uuid_is_version_4 );
        RUN_TEST( uuid_roundabout );
	RUN_TEST( uuid_to_from_null_str );
	RUN_TEST( uuid_from_string );
}
GREATEST_MAIN_DEFS();

int main( int argc, char **argv )
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE( uuid );
    GREATEST_MAIN_END();
}
