#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os_xml.h"



int main(int argc, char ** argv)
{
    int i = 0;
    OS_XML xml;

/**
 *  XML_NODE ** xml_node
 */
    XML_NODE node = NULL;


    /* File name must be given */
    if(argc < 2)
    {
        printf("Usage: %s file\n",argv[0]);
        return(-1);
    }


    /* Reading the XML. Printing error and line number */
    if(OS_ReadXML(argv[1],&xml) < 0)
    {
        printf("OS_ReadXML error: %s, line :%d\n",xml.err, xml.err_line);
        return(1);
    }

/*
    printf("++++%d++++\n",xml.cur);
    printf("++++%d++++\n",xml.fol);

	int j=0;

	for(;i<xml.cur;i++)
	{

			printf("++++%d++++\n",xml.tp[i]);
			printf("++++%d++++\n",xml.rl[i]);
			printf("++++%d++++\n",xml.ck[i]);
			printf("++++%d++++\n",xml.ln[i]);
			j=i+1;

			printf("+content+++%s++++\n",xml.ct[i]);
			printf("+elementOrattribute+++%s++++\n",xml.el[i]);
			printf("**************************\n");

*/

/*
			for(;j<xml.cur;j++)
			{

				if(xml.rl[j]==i)
				{
					
						printf("++++%s++++\n",xml.ct[i][j]);
						printf("++++%s++++\n",xml.el[i][j]);

				}

			}	

*/


	}		

    if(OS_ApplyVariables(&xml) != 0)
    {
	    printf("OS_ReadXML error: Applying variables: %s\n", xml.err);
	    return(1);
    }

    /* Getting all nodes */
    node = OS_GetElementsbyNode(&xml,NULL);
    if(node == NULL)
    {
	    printf("OS_GetElementsbyNode error: %s, line: %d\n", xml.err, xml.err_line);
        return(1);
    }

    i = 0;

    while(node[i])
    {
        int j = 0;
        XML_NODE cnode;

        cnode = OS_GetElementsbyNode(&xml, node[i]);
        if(cnode == NULL)
        {
            i++;
            continue;
        }

        while(cnode[j])
        {
            printf("Element: %s -> %s\n",
                    cnode[j]->element,
                    cnode[j]->content);
            if(cnode[j]->attributes && cnode[j]->values)
            {
                int k = 0;
                while(cnode[j]->attributes[k])
                {
                    printf("attr %s:%s\n",
                           cnode[j]->attributes[k],
                           cnode[j]->values[k]);
                    k++;
                }
            }
            j++;
        }

        OS_ClearNode(cnode);
        i++;
    }

    /* Clearing the nodes */
    OS_ClearNode(node);

    node = NULL;

    OS_ClearXML(&xml);

    return(0);
}