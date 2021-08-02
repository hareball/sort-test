
/*
 * sort-test
 * 
 * Copyright (C) 2021 Dan Hare
 *
 * This file is part of sort-test, a free suite of sort algorithms
 *
 * sort-test is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * sort-test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
 
#include "sort-test.h"

char *color_code( char *dest, const char *code, int bold )
{
    if( SHOW_COLOUR )
    {
        sprintf( dest, "%s%s%sm",
                COLOUR_START,
                (bold ? C_NORMAL : C_BOLD ),
                code );
    }
    else
    {
        strcpy( dest, "" );
    }
    
    return( dest );
}

void add_colour( char *dest, const char *src )
{
    char buf[MAX_STRING_SIZE];
    const char *str;
    const char *i = '\0';
    char *point;

    point = dest;
    str   = src;
    while( *str != '\0' )
    {
    if( *str != '@' )
    {
        *point++ = *str++;
        continue;
    }

    ++str;
    switch( *str )
    {
        default:    sprintf( buf, "@%c", *str );
            i = buf;                                            break;
        case '@':   i = "@";                                    break;
        case 'l':   i = color_code( buf, CF_BLACK, FALSE );     break;
        case 'L':   i = color_code( buf, CF_BLACK, TRUE );      break;
        case 'r':   i = color_code( buf, CF_RED, FALSE );       break;
        case 'R':   i = color_code( buf, CF_RED, TRUE );        break;
        case 'g':   i = color_code( buf, CF_GREEN, FALSE );     break;
        case 'G':   i = color_code( buf, CF_GREEN, TRUE );      break;
        case 'y':   i = color_code( buf, CF_YELLOW, FALSE );    break;
        case 'Y':   i = color_code( buf, CF_YELLOW, TRUE );     break;
        case 'b':   i = color_code( buf, CF_BLUE, FALSE );      break;
        case 'B':   i = color_code( buf, CF_BLUE, TRUE );       break;
        case 'm':   i = color_code( buf, CF_MAGENTA, FALSE );   break;
        case 'M':   i = color_code( buf, CF_MAGENTA, TRUE );    break;
        case 'c':   i = color_code( buf, CF_CYAN, FALSE );      break;
        case 'C':   i = color_code( buf, CF_CYAN, TRUE );       break;
        case 'w':   i = color_code( buf, CF_WHITE, FALSE );     break;
        case 'W':   i = color_code( buf, CF_WHITE, TRUE );      break;                                 
        case 'f':   i = color_code( buf, C_NORMAL, FALSE );     break;
        case 'F':   i = color_code( buf, C_FLASH, FALSE );      break;

        case 'k':
        ++str;
        switch( tolower( *str ) )
        {
            default:    sprintf( buf, "@k%c", *str );
                i = buf;                                            break;
            case 'n':
            case 'l':   i = color_code( buf, CF_BLACK, TRUE );      break;
            case 'r':   i = color_code( buf, CB_RED, TRUE );        break;
            case 'g':   i = color_code( buf, CB_GREEN, TRUE );      break;
            case 'y':   i = color_code( buf, CB_YELLOW, TRUE );     break;
            case 'b':   i = color_code( buf, CB_BLUE, TRUE);        break;
            case 'm':   i = color_code( buf, CB_MAGENTA, TRUE );    break;
            case 'c':   i = color_code( buf, CB_CYAN, TRUE );       break;
            case 'w':   i = color_code( buf, CB_WHITE, TRUE );      break;
        }
        break;
    }
    ++str;
    while( ( *point = *i ) != '\0' )
        ++point, ++i;
    }

    *point = '\0';

    return;
}
