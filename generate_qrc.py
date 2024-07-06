import json
import os
import shutil
import sys
import xml.etree.ElementTree

# Directories
RESOURCES: str = ''
IMAGES: str = ''
AUDIOS: str = ''
QRC: str = ''
QRC_BAK: str = ''
QRC_JSON: str = ''
QRC_JSON_BAK: str = ''


# Function to add files to qrc content
def add_files_to_qrc(directory, alias_prefix, qrc_lines):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif', '.wav', '.mp3', '.ogg')):
                # here we're guaranteed that the `root` and `file` is `LiteralString` (a.k.a. `str`) so just cast them
                # Ensure forward slashes
                relative_path = os.path.relpath(str(os.path.join(root, file)), directory).replace("\\", "/")
                alias = os.path.join(alias_prefix, os.path.basename(file)).replace("\\", "/")
                qrc_lines.append(f'        <file alias="{alias}">{directory}{relative_path}</file>\n')


def gen_qrc(images: str, audios: str) -> None:
    # QRC file paths

    # Backup the existing QRC file if it exists
    if os.path.exists(QRC):
        shutil.copy(QRC, QRC_BAK)

    # Generate qrc content
    qrc_lines: listy[str] = [
        '<!DOCTYPE RCC>\n',
        '<RCC version="1.0">\n',
        '    <qresource prefix="/">\n'
    ]

    add_files_to_qrc(images, "images", qrc_lines)
    add_files_to_qrc(audios, "audios", qrc_lines)

    qrc_lines.append('    </qresource>\n')
    qrc_lines.append('</RCC>\n')

    # Write qrc content to file
    with open(QRC, "w") as qrc_file:
        qrc_file.writelines(qrc_lines)

    print(f"QRC file generated at {QRC}.")


def parse_qrc_to_json(qrc_file: str, qrc_json: str) -> None:
    tree: xml.etree.ElementTree = xml.etree.ElementTree.parse(qrc_file)
    root = tree.getroot()
    resources: dict[str, list[LiteralString]] = {"images": [], "audios": []}
    for file_line in root.findall(".//file"):
        file_path: str = file_line.text
        alias: str = file_line.get('alias')

        if "images" in alias:
            relative_path: list[LiteralString] = file_path.split('images/', 1)[-1]
            resources["images"].append(relative_path)
        elif "audios" in alias:
            relative_path: list[LiteralString] = file_path.split('audios/', 1)[-1]
            resources["audios"].append(relative_path)
    else:
        # raise FileNotFoundError
        pass

    if os.path.exists(qrc_json):
        shutil.copy(qrc_json, QRC_JSON_BAK)

    with open(qrc_json, 'w') as file:
        json.dump(resources, file, indent=4)

    print(f"json file generated at {qrc_json}.")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Please provide Cmake Source Directory and output qrc file path as argument.")
        sys.exit(1)
    RESOURCES = sys.argv[1] + '/Resources/'
    IMAGES = RESOURCES + 'images/'
    AUDIOS = RESOURCES + 'audios/'
    QRC = sys.argv[2]
    QRC_BAK = QRC + '.bak'
    gen_qrc(IMAGES, AUDIOS)
    QRC_JSON = sys.argv[3]
    QRC_JSON_BAK = QRC_JSON + '.bak'
    parse_qrc_to_json(QRC, QRC_JSON)
else:
    pass
