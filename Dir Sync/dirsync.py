import os
import glob
import filecmp
import argparse
import shutil
from stat import *

class DirSync:
    ''' Class to synchronize directories - all files in source directory will be copied
        to destination directory '''

    def __init__(self, name, source_dir, destination_dir, warnings, debug):
        self.name = name
        self.node_list = [source_dir, destination_dir]
        self.file_copied_count = 0
        self.folder_copied_count = 0
        self.current_node = 0
        self.warning_only = warnings
        self.debug_level = int(debug)

    def compare_trees(self):
        if len(self.node_list) % 2 != 0:
            print("Error: Node list must be multiple of 2")
            return False
        for idx in range(0,len(self.node_list),2):
            source = self.node_list[idx].root_path
            destination = self.node_list[idx+1].root_path
            print("Sync source directory {} with destination directory {}".format(source,destination))
            self.current_node = idx
            for subdir_path in glob.glob('{}/{}'.format(source,'*/')):
                subdir_name = subdir_path.split('/')[-2]
                if self.debug_level > 0:
                    print("Processing dir {}".format(subdir_name))
                tar_dir = destination + '/' + subdir_name
                src_dir = source + '/' + subdir_name
                self._compare_directories(tar_dir,src_dir)

                files = os.listdir(source)
                files = [f for f in os.listdir(source) if os.path.isfile(os.path.join(source,f))]
                print("length of files: ", len(files), " Source: ", source)
            for file in files:
                file_name, file_ext = os.path.splitext(file)
                file_ext = file_ext.lstrip('.')
                if any(ext == file_ext for ext in self.node_list[self.current_node].file_ext_exempt):
                    if self.debug_level > 0:
                        print("exempted file: {}".format(file))
                    continue
                self.file_copied_count = self.file_copied_count + 1
                src_file = os.path.join(source,file)
                if self.warning_only:
                    print('Warning: file copy \"' + src_file + '\" to \"' + destination + '\"')
                else:
                    shutil.copy2(src_file, destination)
                    print('Copied \"' + src_file + '\" to \"' + destination + '\"')

        return True

    def _compare_directories(self, left, right):
        ''' This method compares directories. If there is a common directory, the
            algorithm must compare what is inside of the directory by calling this
            recursively.
        '''
        if not os.path.isdir(left):
            self.folder_copied_count = self.folder_copied_count + 1
            if self.warning_only:
                print ('Warning: directory copy from {} to {}'.format(right,left))
                return
            else:
                os.makedirs(left)
                self._Duplicate_DirTree(right,left)

        comparison = filecmp.dircmp(left, right)
        if comparison.common_dirs:
            for d in comparison.common_dirs:
                self._compare_directories(os.path.join(left, d), os.path.join(right, d))
        if comparison.right_only:
            self._copy(comparison.right_only, right, left)
        left_newer = []
        right_newer = []
        if comparison.diff_files:
            for d in comparison.diff_files:
                l_modified = os.stat(os.path.join(left, d)).st_mtime
                r_modified = os.stat(os.path.join(right, d)).st_mtime
                if l_modified < r_modified:
                    right_newer.append(d)
        self._copy(right_newer, right, left)

    def _copy(self, file_list, src, dest):
        ''' This method copies a list of files from a source node to a destination node '''
        for f in file_list:
            if any(ext in f for ext in self.node_list[self.current_node].file_ext_exempt):
                if self.debug_level > 0:
                    print("exempted file extension {}".format(os.path.join(src,f)))
                continue

            srcpath = os.path.join(src, os.path.basename(f))
            if os.path.isdir(srcpath):
                self.folder_copied_count = self.folder_copied_count + 1
                if self.warning_only:
                    print('Warning: directory copy \"' + os.path.basename(srcpath) + '\" from \"' + \
                          os.path.dirname(srcpath) + '\" to \"' + dest + '\"')
                else:
                    shutil.copytree(srcpath, os.path.join(dest, os.path.basename(f)), \
                                    ignore=self.node_list[self.current_node].file_ext_exempt)
                    print('Copied directory \"' + os.path.basename(srcpath) + '\" from \"' + \
                          os.path.dirname(srcpath) + '\" to \"' + dest + '\"')
            else:
                self.file_copied_count = self.file_copied_count + 1
                if self.warning_only:
                    print('Warning: file copy \"' + os.path.basename(srcpath) + '\" from \"' + \
                          os.path.dirname(srcpath) + '\" to \"' + dest + '\"')
                else:
                    shutil.copy2(srcpath, dest)
                    print('Copied \"' + os.path.basename(srcpath) + '\" from \"' + \
                          os.path.dirname(srcpath) + '\" to \"' + dest + '\"')

    def _Duplicate_DirTree(self,src,target):
        dir_list =  os.listdir(src)
        for dir in dir_list:
            if os.path.isdir(os.path.join(src,dir)):
                os.makedirs(os.path.join(target,dir))
                self._Duplicate_DirTree(os.path.join(src,dir),os.path.join(target,dir))


class Node:
    ''' This class represents a node in a DirSync synchronization '''
    def __init__(self, path, name='', fileExempt = []):
        self.name = name
        self.root_path = os.path.abspath(path)
        self.file_list = os.listdir(self.root_path)
        self.file_ext_exempt = fileExempt


if __name__ == "__main__":

    p = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    p.add_argument('s', help='Source directory to syn from')
    p.add_argument('d', help='Destination directory to sync to')
    p.add_argument('-w', '--warning',dest='warning',action='store_true',help='Issue Warnings only - do not copy files')
    p.add_argument('-d', '--debug',dest='debug_level',action='store', help='Set debug level higher than 0 to see more messages',default= '0')
    args = p.parse_args()

    warnings = False
    if args.warning:
        warnings = True

    file_ext_exempt = ['pyc', 'tmp','bak','old','pdf']

    src_node = Node(args.s, 'node1', file_ext_exempt)
    dest_node = Node(args.d, 'node2')
    dirsync = DirSync('DirSync', src_node, dest_node, warnings, args.debug_level )
    dirsync.compare_trees()
    print('Total files copied ' + str(dirsync.file_copied_count))
    print('Total folders copied ' + str(dirsync.folder_copied_count))


