/*
 * CCarmack.h
 *
 *  Created on: 30.05.2010
 *      Author: gerstrong
 *
 *  Integration of the Carmack decompression routine to Commander Genius described as class
 */

#ifndef CCARMACK_H_
#define CCARMACK_H_

#include <vector>
#include <base/TypeDefinitions.h>

class CCarmack
{
public:	
    void expand(std::vector<gs_byte>& dst,
                std::vector<gs_byte>& src ,
                const size_t decarmacksize);
};

#endif /* CCARMACK_H_ */
