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
  <a href="#what-is-sequencer">Highlights</a> •
  <a href="#simple-to-get-started">Get Started</a> •
  <a href="#download">Download</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#credits--attributions">Credits</a> •
  <a href="#license">License</a>
</p>

## :white_check_mark: What is sequencer?

Sequencer allows you to create **simple and clear sequence diagrams**, based on a simple grammar. Your diagram is **drawn in real-time** as you type, and is designed to be:

 - easy to **edit**
 - easy to **share**
 - easy to **version control**

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

Copy the diagram to your clipboard to paste straight in to chat or email.

See the [wiki](https://github.com/rsouth/sequencer/wiki/Grammar) for the current grammar.


## :movie_camera: Demo

<div align="center" style="display: flex; flex-direction: column;">
  <p>
    <img src="https://s7.gifyu.com/images/sequence-gizmo-6.gif" alt="sequence-gizmo-6.gif" border="0" />
  </p>
</div>

_(Demo is recorded from jSequencer, I will replace with a recording of the Sequencer C++ re-write soon)_


## :hammer: Building

```Batchfile
qmake
nmake release
```

https://github.com/rsouth/sequencer/wiki/Building


## :rocket: Download

Coming soon


## :thumbsup: Contributing

**Pull requests are welcome**. For major changes, please open an issue first to discuss what you would like to change.


## :pray: Credits / Attributions

#### :art: Icons

Toolbar icons made by [Dave Gandy](https://www.flaticon.com/authors/dave-gandy) from [www.flaticon.com](https://www.flaticon.com/).


#### :bulb: Inspiration

[WebSequenceDiagrams](https://www.websequencediagrams.com/) which is an online text-based sequence diagram generator with a commercial offering.

Sequencer is a C++ re-write of my own project [jSequencer](https://github.com/rsouth/jsequencer).


## :blue_book: License

This project is licensed under the terms of the GNU General Public License v3.0.

