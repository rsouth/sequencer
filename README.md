<div align="center" style="display: flex; flex-direction: column;">
  <img src="./public/banner-logo.png" alt="sequencer logo" width="500px" />
  <h3>sequencer is a simple diagramming tool to make it easy for developers to share ideas</h3>
  <p>
    <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/rsouth/sequencer">
    <img alt="GPL v3 License" src="https://img.shields.io/github/license/rsouth/sequencer">
    <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/rsouth/sequencer">
  </p>
</div>

<p align="center">
  <a href="#white_check_mark-what-is-sequencer">Highlights</a> •
  <a href="#zap-simple-to-get-started">Get Started</a> •
  <a href="#movie_camera-demo">Demo</a> •
  <a href="#art-themes">Themes</a> •
  <a href="#rocket-download">Download</a> •
  <a href="#thumbsup-contributing">Contributing</a> •
  <a href="#pray-credits--attributions">Credits</a> •
  <a href="#blue_book-license">License</a>
</p>

## :white_check_mark: What is sequencer?

Sequencer allows you to create **simple and clear sequence diagrams**, based on a simple grammar. Your diagram is **drawn in real-time** as you type, and is designed to be:

 - easy to **edit**
 - easy to **share**
 - easy to **version control**

Sequencer is **free** and **open-source**, distributed as a **single .exe (no installer)**, and has just the features you need to share and document your idea quickly.


## :movie_camera: Demo

<div align="center" style="display: flex; flex-direction: column;">
  <p>
    <img src="https://s8.gifyu.com/images/sequencer-0-0-2-0-demo.gif" alt="sequence-gizmo-6.gif" border="0" />
  </p>
</div>


## :zap: Simple to get started

#### :speech_balloon: Describe your sequence

```
Client -> Server: Request
Server -> Server: Parses request
Server -> Service: Query
Service -> Server: Data
Server -> Client: Response
```


#### :boom: Your diagram is ready to go

<img src="https://i.ibb.co/FDT8kNL/sequencer-example-2020-08-07.png" alt="sequencer-example-2020-08-07" border="0" />

 - paste right in to chat, email, your wiki page
 - export as a .png file
 - share the source, or better yet - version control it!

See the [Grammar page on the wiki](https://github.com/rsouth/sequencer/wiki/Grammar) for details of the current grammar.


## :art: Themes

Support for basic themes is progressing, the "Sketchy" theme is available on the `develop` branch and expect to be included in the next release.

<img src="https://i.ibb.co/rFv8X7V/image.png" alt="image" border="0">

Theme information can be found on the [Themes wiki page](https://github.com/rsouth/sequencer/wiki/Themes).


## :hammer: Building

```Batchfile
qmake
nmake release
```

https://github.com/rsouth/sequencer/wiki/Building


## :rocket: Download

[Releases Page](https://github.com/rsouth/sequencer/releases)

#### [Latest](https://github.com/rsouth/sequencer/releases/latest)

Please download the [latest](https://github.com/rsouth/sequencer/releases/latest) release.

#### [v0.0.2 pre-alpha](https://github.com/rsouth/sequencer/releases/tag/v0.0.2-pre-alpha) :cherries:

 - Rendering is now done in Qt QPainter on a QPixmap rather than using CImg
 - More functional UI
   - Dirty checks before New, Open
   - Create New button works
   - Undo/redo functionality in text editor
 - Code review items since last release
 - Rendering changes:
   - Default font sizes are now smaller
   - Smaller arrow-heads
   - Rounded boxes around participant headers
   
   
#### [v0.0.1 pre-alpha](https://github.com/rsouth/sequencer/releases/tag/v0.0.1-pre-alpha)

 - Grammar parity with jSequencer
    - Participants and messages
    - Synchronous and asynchronous messages
    - Self-referential messages
    - Reply messages
    - Header information (title, author, date)
 - Qt UI implementation
 - Sharing options (clipboard, .png export)


## :thumbsup: Contributing

**Pull requests are welcome**. For major changes, please open an issue first to discuss what you would like to change.


## :pray: Credits / Attributions

#### :framed_picture: Icons

Toolbar icons made by [Dave Gandy](https://www.flaticon.com/authors/dave-gandy) from [www.flaticon.com](https://www.flaticon.com/).


#### :bulb: Inspiration

[WebSequenceDiagrams](https://www.websequencediagrams.com/) which is an online text-based sequence diagram generator with a commercial offering.

Sequencer is a C++ re-write of my own project [jSequencer](https://github.com/rsouth/jsequencer).


## :blue_book: License

This project is licensed under the terms of the GNU General Public License v3.0.

