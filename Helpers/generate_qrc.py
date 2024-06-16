import os
import shutil
import sys

# Directories
RESOURCES = []
IMAGES = []
AUDIOS = []
QRC = []
QRC_BAK =[]


# Function to add files to qrc content
def add_files_to_qrc(directory, alias_prefix, qrc_lines):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif', '.wav', '.mp3', '.ogg')):
                relative_path = os.path.relpath(os.path.join(root, file), directory)
                relative_path = relative_path.replace("\\", "/")  # Ensure forward slashes
                alias = os.path.join(alias_prefix, os.path.basename(file)).replace("\\", "/")
                qrc_lines.append(f'        <file alias="{alias}">{directory}{relative_path}</file>\n')


def gen_qrc(images: str, audios: str) -> None:
    # QRC file paths

    # Backup the existing QRC file if it exists
    if os.path.exists(QRC):
        shutil.copy(QRC, QRC_BAK)

    # Generate qrc content
    qrc_lines = [
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


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Please provide Cmake Source Directory and output qrc file path as argument.")
        sys.exit(1)
    RESOURCES = sys.argv[1] + '/Resources/'
    IMAGES = RESOURCES + 'images/'
    AUDIOS = RESOURCES + 'audios/'
    QRC = sys.argv[2]
    QRC_BAK = QRC + '.bak'
    gen_qrc(IMAGES, AUDIOS)
else:
    pass
