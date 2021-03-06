/*
 * Library seek testing program
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "vhdi_test_libcerror.h"
#include "vhdi_test_libcstring.h"
#include "vhdi_test_libvhdi.h"
#include "vhdi_test_unused.h"

/* Define to make vhdi_test_seek generate verbose output
#define VHDI_TEST_SEEK_VERBOSE
 */

/* Tests libvhdi_file_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_offset(
     libvhdi_file_t *file,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libvhdi_file_seek_offset(
	                 file,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libvhdi_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libvhdi_error_free(
		 &error );
	}
	return( result );
}

/* Tests seeking in a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek(
     libvhdi_file_t *file,
     size64_t media_size )
{
	int result = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( media_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Media size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	result = vhdi_test_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size>
	 * Expected result: <media_size>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          (off64_t) media_size,
	          SEEK_SET,
	          (off64_t) media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size / 5>
	 * Expected result: <media_size / 5>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          (off64_t) ( media_size / 5 ),
	          SEEK_SET,
	          (off64_t) ( media_size / 5 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size + 987>
	 * Expected result: <media_size + 987>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          (off64_t) ( media_size + 987 ),
	          SEEK_SET,
	          (off64_t) ( media_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	result = vhdi_test_seek_offset(
	          file,
	          -987,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <media_size + 987>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          0,
	          SEEK_CUR,
	          (off64_t) ( media_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (media_size + 987)>
	 * Expected result: 0
	 */
	result = vhdi_test_seek_offset(
	          file,
	          -1 * (off64_t) ( media_size + 987 ),
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <media_size / 3>
	 * Expected result: <media_size / 3>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          (off64_t) ( media_size / 3 ),
	          SEEK_CUR,
	          (off64_t) ( media_size / 3 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	if( media_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: 0
		 */
		result = vhdi_test_seek_offset(
		          file,
		          -2 * (off64_t) ( media_size / 3 ),
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: -1
		 */
		result = vhdi_test_seek_offset(
		          file,
		          -2 * (off64_t) ( media_size / 3 ),
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <media_size>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          (off64_t) media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * media_size>
	 * Expected result: 0
	 */
	result = vhdi_test_seek_offset(
	          file,
	          -1 * (off64_t) media_size,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size / 4)>
	 * Expected result: <media_size - (media_size / 4)>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          -1 * (off64_t) ( media_size / 4 ),
	          SEEK_END,
	          (off64_t) media_size - (off64_t) ( media_size / 4 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <media_size + 542>
	 */
	result = vhdi_test_seek_offset(
	          file,
	          542,
	          SEEK_END,
	          (off64_t) ( media_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size + 542)>
	 * Expected result: -1
	 */
	result = vhdi_test_seek_offset(
	          file,
	          -1 * (off64_t) ( media_size + 542 ),
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = vhdi_test_seek_offset(
	          file,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* Tests seeking in a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_file(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libvhdi_file_t *file = NULL;
	size64_t media_size  = 0;
	int result           = 0;

	if( libvhdi_file_initialize(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvhdi_file_open_wide(
	     file,
	     source,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#else
	if( libvhdi_file_open(
	     file,
	     source,
	     LIBVHDI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( libvhdi_file_get_media_size(
	     file,
	     &media_size,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve media size.\n" );

		goto on_error;
	}
	result = vhdi_test_seek(
	          file,
	          media_size );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file.\n" );

		goto on_error;
	}
	if( libvhdi_file_close(
	     file,
	     error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( libvhdi_file_free(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( file != NULL )
	{
		libvhdi_file_close(
		 file,
		 NULL );
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( -1 );
}

/* Tests seeking in a file without opening it
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vhdi_test_seek_file_no_open(
     libcstring_system_character_t *source VHDI_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvhdi_file_t *file  = NULL;
	off64_t result_offset = 0;
	int result            = 0;

	VHDI_TEST_UNREFERENCED_PARAMETER( source );

	if( libvhdi_file_initialize(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Testing seek without open: \t" );

	result_offset = libvhdi_file_seek_offset(
	                 file,
	                 0,
	                 SEEK_SET,
	                 error );

	if( result_offset == -1 )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( ( error != NULL )
	 && ( *error != NULL ) )
	{
		if( result != 1 )
		{
			libvhdi_error_backtrace_fprint(
			 *error,
			 stderr );
		}
		libvhdi_error_free(
		 error );
	}
	if( libvhdi_file_free(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( file != NULL )
	{
		libvhdi_file_free(
		 &file,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcstring_system_character_t *source = NULL;
	int result                            = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ 1 ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( VHDI_TEST_SEEK_VERBOSE )
	libvhdi_notify_set_verbose(
	 1 );
	libvhdi_notify_set_stream(
	 stderr,
	 NULL );
#endif
	result = vhdi_test_seek_file(
	          source,
	          &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file.\n" );

		goto on_error;
	}
	result = vhdi_test_seek_file_no_open(
	          source,
	          &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file without open.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libvhdi_error_backtrace_fprint(
		 error,
		 stderr );
		libvhdi_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

