/*
    This file is part of the DISH programming language, Copyright 2014, 2015,
    2016 by Chris Buck.
    
    DISH is free software for non-commercial use: you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014-2017 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <dirent.h>
#include <sys/stat.h>

#include "langfilesys.h"
#include "langtime.h"

/******************************************************************************

    Public function definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateFileSysFileT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< BooleanTypeAtomic > boolean_type(BooleanTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Name", StringTypeAtomic::MakeValue());
        structure->Add("Directory", boolean_type);
        structure->Add("Size", boolean_type);
    }
    
    return structure;
}

std::shared_ptr< dish::iAtomic > dish::CreateFileSysDirT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Name", StringTypeAtomic::MakeValue());
        structure->Add("Directory", BooleanTypeAtomic::MakeValue());
        structure->Add("Contents", ArrayTypeAtomic::MakeValue(0));
    }
    
    return structure;
}

std::shared_ptr< dish::iAtomic > dish::CreateFileInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Name", StringTypeAtomic::MakeValue());
        structure->Add("DateAccessed", integer_type);
        structure->Add("DateModified", integer_type);
        structure->Add("Size", integer_type);
    }
    
    return structure;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

namespace
{

    std::shared_ptr< dish::iAtomic > CreateFileSysFile(const dish::StringT &name)
    {
        std::shared_ptr< dish::iAtomic > object(dish::CreateFileSysFileT()->Declare());
        object->Member("Name")->Assign(name);
        object->Member("Directory")->Assign(false);

        return object;
    }

    std::shared_ptr< dish::iAtomic > CreateFileSysDir(const dish::StringT &name)
    {
        std::shared_ptr< dish::iAtomic > object(dish::CreateFileSysDirT()->Declare());
        object->Member("Name")->Assign(name);
        object->Member("Directory")->Assign(true);

        return object;
    }

    std::shared_ptr< dish::iAtomic > CreateFileInfo(const dish::StringT &name, const std::time_t &accessed, const std::time_t &modified, const dish::IntegerT &size)
    {
        std::shared_ptr< dish::iAtomic > object(dish::CreateFileInfoT()->Declare());
        object->Member("Name")->Assign(name);
        object->Member("DateAccessed")->Assign(dish::IntegerValue::MakeValue(accessed));
        object->Member("DateModified")->Assign(dish::IntegerValue::MakeValue(modified));
        object->Member("Size")->Assign(dish::IntegerValue::MakeValue(size));

        return object;
    }

    void BuildFileSystemTree(std::shared_ptr< dish::iAtomic > pathtree, const dish::StringT &path, const dish::BooleanT &recurse)
    {
        int result(0);

        //  Get information about the named entity (specified by 'path').
        struct stat statbuf;
        result = lstat(path.c_str(), &statbuf);
        assert(result >= 0);
        
        //  Do we have a directory?
        if(0 == S_ISDIR(statbuf.st_mode))
        {
            //  No, this is a file. Add it to the path-tree.
            pathtree->Member("Contents")->Add(CreateFileSysFile(path));
        }
        else
        {
            //  Yes; create an object for the subdirectory.
            std::shared_ptr< dish::iAtomic > subdir(CreateFileSysDir(path));
            
            //  Are we to recurse through subdirectories?
            if(recurse)
            {
                //  Yes; build the base-directory.
                const dish::StringT basedir(path + "/");
                
                //  Open the directory.
                DIR *dp(opendir(basedir.c_str()));
                
                if(NULL != dp)
                {
                    //  Loop through the contents of the directory.
                    for(struct dirent *dptr(readdir(dp)); NULL != dptr; dptr = readdir(dp))
                    {
                        if((0 != strcmp(dptr->d_name, ".")) && (0 != strcmp(dptr->d_name, "..")))
                        {
                            BuildFileSystemTree(subdir, basedir + dptr->d_name, recurse);
                        }
                    }
                    
                    //  Close the directory.
                    result = closedir(dp);
                    assert(result >= 0);
                }
            }
            
            //  Add the subdirectory to the path-tree.
            pathtree->Member("Contents")->Add(subdir);
        }
    }

    void CollectFiles(std::shared_ptr< dish::iAtomic > array, const dish::StringT &path, const dish::BooleanT &recurse)
    {
        int result(0);

        //  Get information about the named entity (specified by 'path').
        struct stat statbuf;
        result = lstat(path.c_str(), &statbuf);
        assert(result >= 0);
        
        //  Do we have a directory?
        if(0 == S_ISDIR(statbuf.st_mode))
        {
            //  No, this is a file. Add it to the path-tree.
            array->Add(dish::StringValue::MakeValue(path));
        }
        else
        {
            //  Yes; are we to recurse through subdirectories?
            if(recurse)
            {
                //  Yes; build the base-directory.
                const dish::StringT basedir(path + "/");
                
                //  Open the directory.
                DIR *dp(opendir(basedir.c_str()));
                
                if(NULL != dp)
                {
                    //  Loop through the contents of the directory.
                    for(struct dirent *dptr(readdir(dp)); NULL != dptr; dptr = readdir(dp))
                    {
                        if((0 != strcmp(dptr->d_name, ".")) && (0 != strcmp(dptr->d_name, "..")))
                        {
                            CollectFiles(array, basedir + dptr->d_name, recurse);
                        }
                    }
                    
                    //  Close the directory.
                    result = closedir(dp);
                    assert(result >= 0);
                }
            }
        }
    }

    void CollectDirectories(std::shared_ptr< dish::iAtomic > array, const dish::StringT &path, const dish::BooleanT &recurse)
    {
        int result(0);

        //  Get information about the named entity (specified by 'path').
        struct stat statbuf;
        result = lstat(path.c_str(), &statbuf);
        assert(result >= 0);
        
        //  Do we have a directory?
        if(0 != S_ISDIR(statbuf.st_mode))
        {
            //  Yes, this is a file. Add it to the path-tree.
            array->Add(dish::StringValue::MakeValue(path));
            
            //  Are we to recurse through subdirectories?
            if(recurse)
            {
                //  Yes; build the base-directory.
                const dish::StringT basedir(path + "/");
                
                //  Open the directory.
                DIR *dp(opendir(basedir.c_str()));
                
                if(NULL != dp)
                {
                    //  Loop through the contents of the directory.
                    for(struct dirent *dptr(readdir(dp)); NULL != dptr; dptr = readdir(dp))
                    {
                        if((0 != strcmp(dptr->d_name, ".")) && (0 != strcmp(dptr->d_name, "..")))
                        {
                            CollectDirectories(array, basedir + dptr->d_name, recurse);
                        }
                    }
                    
                    //  Close the directory.
                    result = closedir(dp);
                    assert(result >= 0);
                }
            }
        }
    }

    void PrintPathTree(std::shared_ptr< dish::iAtomic > pathtree, const dish::IntegerT indent)
    {
        const std::string pad((indent >= 0) ? indent : 0, ' ');
        
        std::shared_ptr< dish::iAtomic > array(pathtree->Member("Contents"));

        for(dish::IntegerT i(array->Member("start")->AsInteger()), last_i(array->Member("finish")->AsInteger()); i <= last_i; ++i)
        {
            std::cout << pad << array->Element(i)->Member("Name")->AsString() << std::endl;
            
            if(array->Element(i)->Member("Directory")->AsBoolean())
            {
                PrintPathTree(array->Element(i), (indent >= 0) ? (indent + 4) : indent);
            }
        }
    }

}

/******************************************************************************

    dish::FILESYS_FileExistsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_FileExistsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(FileExists(getParam(symtab, "fname")->AsString()));
}

/******************************************************************************

    dish::FILESYS_ReadLocationFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_ReadLocationFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT rootdir(getParam(symtab, "rootdir")->AsString());

    std::shared_ptr< iAtomic > dir(CreateFileSysDir(rootdir));
    BuildFileSystemTree(
        dir, 
        rootdir, 
        getParam(symtab, "recurse")->AsBoolean()
    );
    
    return dir;
}

/******************************************************************************

    dish::FILESYS_ReadFilesFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_ReadFilesFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > array(ArrayValue::MakeValue(0));
    CollectFiles(
        array, 
        getParam(symtab, "rootdir")->AsString(), 
        getParam(symtab, "recurse")->AsBoolean()
    );
    
    return array;
}

/******************************************************************************

    dish::FILESYS_ReadDirectoriesFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_ReadDirectoriesFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > array(ArrayValue::MakeValue(0));
    CollectDirectories(
        array, 
        getParam(symtab, "rootdir")->AsString(), 
        getParam(symtab, "recurse")->AsBoolean()
    );
    
    return array;
}

/******************************************************************************

    dish::FILESYS_GetFileInfoFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_GetFileInfoFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT fname(getParam(symtab, "fname")->AsString());

    //  Get the file information.
    struct stat fstat;
    const int result(stat(fname.c_str(), &fstat));
    assert(0 == result);
    
    return CreateFileInfo(
        fname,
        static_cast< IntegerT >(fstat.st_atime),
        static_cast< IntegerT >(fstat.st_mtime),
        static_cast< IntegerT >(fstat.st_size)
    );
}

/******************************************************************************

    dish::FILESYS_PrintPathTree1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_PrintPathTree1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    PrintPathTree(
        getParam(symtab, "pathtree"),
        0
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::FILESYS_PrintPathTreeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FILESYS_PrintPathTreeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    PrintPathTree(
        getParam(symtab, "pathtree"),
        getParam(symtab, "indent")->AsInteger()
    );
    
    return NullValue::MakeValue();
}

