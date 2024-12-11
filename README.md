# CMDPaint

_by setghm_

CMDPaint is a Windows console (CMD) application designed to facilitate the creation of color arrays for the creation of color video games that run on the command line.

The application is designed to be very simple, you can load files and open already created files.

The editor has 4 tools: The **pencil**, the **paint bucket**, the **color picker** and the **grid**.

## Examples

<div style="display:flex; gap: 10px">
  <img src="https://github.com/user-attachments/assets/89e0e7a2-5de3-4cb6-817b-92187921f875" width="350">
  <img src="https://github.com/user-attachments/assets/6ca0b232-44e2-42c7-a045-37c57465db63" width="350">
</div>
<div style="display:flex; gap: 10px">
  <img src="https://github.com/user-attachments/assets/b54de81a-3cbd-4742-bde4-6dd02f8846bc" width="350">
  <img src="https://github.com/user-attachments/assets/3a082ac8-f4c4-4f14-83b7-fb6fbf5a592f" width="350">
</div>

You can test the application with these sample files located at `/examples` folder.

## Output files

The output files have the extension `.bytecolor` which means that they are simple color arrays accepted by the Windows console.

The format is as follows:

- The first 32 bits are used to store the width of the image (unsigned integer).
- The next 32 bits are used to store the height of the image (unsigned integer).
- All other bytes are Windows console colors encoded in 4 bits (1 nibble) each.

> [!NOTE]
> The width and height refer to the **size in characters**, not in pixels.

### File structure

The file structure is as follows:

![ByteColor file format](https://github.com/user-attachments/assets/aa910f8a-37a9-4320-b52b-9fc7621da9c0)

