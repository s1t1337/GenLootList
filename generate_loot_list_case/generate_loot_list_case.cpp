#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include "json.hpp"
#include <string>
#include <fstream>
#include <format>


void write_file( const char* fmt)
{
	FILE* f = fopen( "loot_ist.txt" ,  "a+"  );

	fwrite( fmt, strlen( fmt ), 1, f );
	fclose( f );

}

void read_file(std::string_view  name,int id_case = 0, bool skip_case_id = false)
{
	nlohmann::json json;

	if ( std::ifstream in_file( name.data() ); in_file.good( ) )
	{
		json = nlohmann::json::parse( in_file );
		in_file.close( );
	}
	else
		return;

	const int items = json[  "inventory" ][  "items"  ];
	if ( items )
	{
		for ( auto i = 0; i < items; i++ )
		{
			const auto slot = std::string(  "slot_"  ) + std::to_string( i );

			const int m_definition_index = json[  "inventory"  ][ slot ][  "def_index"  ];
			const int m_paint_kit = json[  "inventory"  ][ slot ][  "paint_kit"  ];

			if( skip_case_id )
				if ( id_case == m_definition_index )
					continue;


			const auto loot = "{" + std::format( "{},{}", m_definition_index, m_paint_kit ) + "},\n";
			std::cout << loot.data() << std::endl;
			write_file( loot.c_str() );
		}

		std::cout << "List loot saved" << std::endl;
	}

}

int main()
{
	bool sss = false;
    std::cout << "Loot_list generator v1\n\n\n\n";

	std::cout << "Enter name file:";
	std::string name_file;
	int id_case = 0;
	std::cin >> name_file;
	std::cout << "Enter ID case:";
	std::cin >> id_case;

	read_file( name_file );


	system( "pause" );
    return 0;
}

