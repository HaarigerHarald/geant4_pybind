R"(

"""Dataset initialization

This checks whether all datasets can be found and offers to download missing ones.

"""

import os
import tarfile
import urllib.request
import tempfile
import sys
import shutil
import stat
import hashlib

progress = 0
envs_to_set = dict()

DATASET_URL = "https://cern.ch/geant4-data/datasets"
DATASETS = [
    {"name": "G4NDL",
     "version": "4.7",
     "filename": "G4NDL",
     "envvar": "G4NEUTRONHPDATA",
     "md5sum": "b001a2091bf9392e6833830347672ea2"},

    {"name": "G4EMLOW",
     "version": "8.2",
     "filename": "G4EMLOW",
     "envvar": "G4LEDATA",
     "md5sum": "07773e57be3f6f2ebb744da5ed574f6d"},

    {"name": "PhotonEvaporation",
     "version": "5.7",
     "filename": "G4PhotonEvaporation",
     "envvar": "G4LEVELGAMMADATA",
     "md5sum": "81ff27deb23af4aa225423e6b3a06b39"},

    {"name": "RadioactiveDecay",
     "version": "5.6",
     "filename": "G4RadioactiveDecay",
     "envvar": "G4RADIOACTIVEDATA",
     "md5sum": "acc1dbeb87b6b708b2874ced729a3a8f"},

    {"name": "G4PARTICLEXS",
     "version": "4.0",
     "filename": "G4PARTICLEXS",
     "envvar": "G4PARTICLEXSDATA",
     "md5sum": "d82a4d171d50f55864e28b6cd6f433c0"},

    {"name": "G4PII",
     "version": "1.3",
     "filename": "G4PII",
     "envvar": "G4PIIDATA",
     "md5sum": "05f2471dbcdf1a2b17cbff84e8e83b37"},

    {"name": "RealSurface",
     "version": "2.2",
     "filename": "G4RealSurface",
     "envvar": "G4REALSURFACEDATA",
     "md5sum": "ea8f1cfa8d8aafd64b71fb30b3e8a6d9"},

    {"name": "G4SAIDDATA",
     "version": "2.0",
     "filename": "G4SAIDDATA",
     "envvar": "G4SAIDXSDATA",
     "md5sum": "d5d4e9541120c274aeed038c621d39da"},

    {"name": "G4ABLA",
     "version": "3.1",
     "filename": "G4ABLA",
     "envvar": "G4ABLADATA",
     "md5sum": "180f1f5d937733b207f8d5677f76296e"},

    {"name": "G4INCL",
     "version": "1.0",
     "filename": "G4INCL",
     "envvar": "G4INCLDATA",
     "md5sum": "85fe937b6df46d41814f07175d3f5b51"},

    {"name": "G4ENSDFSTATE",
     "version": "2.3",
     "filename": "G4ENSDFSTATE",
     "envvar": "G4ENSDFSTATEDATA",
     "md5sum": "6f18fce8f217e7aaeaa3711be9b2c7bf"}
]


def directory_contains(dir, subdir):
    for f in os.listdir(dir):
        if os.path.isdir(os.path.join(dir, f)) and f == subdir:
            return True
    return False


def show_progress(block_num, block_size, total_size):
    global progress
    bar_width = 50
    if block_num == 0:
        sys.stdout.write("[%s]" % (" " * bar_width))
        sys.stdout.flush()
        sys.stdout.write("\b" * (bar_width+1))

    downloaded = int(bar_width * block_num * block_size/total_size)
    if downloaded < bar_width:
        while progress < downloaded:
            sys.stdout.write("#")
            progress += 1
        sys.stdout.flush()
    else:
        while progress < bar_width:
            sys.stdout.write("#")
            progress += 1
        sys.stdout.write("\n")
        sys.stdout.flush()
        progress = 0


def md5_check(file, md5_exp):
    with open(file, 'rb') as f:
        md5_calc = hashlib.md5()
        chunk = f.read(8192)
        while chunk:
            md5_calc.update(chunk)
            chunk = f.read(8192)

        if md5_calc.hexdigest() == md5_exp:
            return True

    return False


def download_dataset(dataset, directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

    filename = dataset["filename"] + "." + dataset["version"] + ".tar.gz"
    url = DATASET_URL + "/" + filename

    print("Downloading data file:", url)
    temp = tempfile.mktemp()
    urllib.request.urlretrieve(url, temp, show_progress)
    if not md5_check(temp, dataset["md5sum"]):
        print("MD5 check failed for", filename)
        os.remove(temp)
        return

    tar = tarfile.open(temp)
    tar.extractall(directory)
    tar.close()
    os.remove(temp)


def ask_for_download(data_directory):
    print("One or more Geant4 datasets were not found.")
    answer = input("Would you like to download the missing ones? [Y/n] ")
    if answer.lower() == 'y' or answer.lower() == 'yes':
        print("Storing data sets at:", data_directory)
        return True
    else:
        return False


def init_datasets():
    global envs_to_set
    data_directory = os.path.join(os.path.expanduser("~"), ".geant4_pybind")
    download_allowed = False

    if "GEANT4_DATA_DIR" in os.environ:
        # Use installed datasets
        return

    if "CI" in os.environ and os.environ["CI"] == "true":
        # Automated tests
        download_allowed = True
        if "HOME" in os.environ:
            data_directory = os.path.join(os.path.realpath(os.environ["HOME"]), ".geant4_pybind")

    for dataset in DATASETS:
        if not dataset["envvar"] in os.environ:
            dirname = dataset["name"] + dataset["version"]
            if not os.path.exists(data_directory) or not directory_contains(data_directory, dirname):
                if download_allowed or ask_for_download(data_directory):
                    download_allowed = True
                    download_dataset(dataset, data_directory)
                else:
                    return

            envs_to_set[dataset["envvar"]] = os.path.join(data_directory, dirname)

    if download_allowed:
        # Clean the data directory
        for data in os.listdir(data_directory):
            if data not in [dataset["name"] + dataset["version"] for dataset in DATASETS]:
                try:
                    def onerror(func, path, info):
                        os.chmod(path, stat.S_IWUSR)
                        func(path)
                    shutil.rmtree(os.path.join(data_directory, data), onerror=onerror)
                except:
                    pass


init_datasets()

# )"
