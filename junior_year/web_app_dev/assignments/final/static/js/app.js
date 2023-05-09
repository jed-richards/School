class Register extends React.Component {

    sendRegisterRequest() {
        let formData = new FormData( document.querySelector('#register-form') );
        fetch('/api/register/', {
            method: 'POST',
            body: formData
        })
        .then(result => result.text())
        .then(
            (result) => {
                if (result == 'ok') {
                    this.props.onRegister();
                }
                else {
                    alert(
                      'Bad username/password/email combo. Username already exists.'
                    );
                }
            },
            (error) => {
                alert('General login error: ' + error);
            }
        )
    }

    render() {
        return (
            <form id="register-form">
             <input
                name="email"
                id="email"
                type="email"
                placeholder="email" />
             <input
                name="username"
                id="username"
                type="text"
                placeholder="username" />
             <input
                name="password"
                id="password"
                type="password"
                placeholder="password" />
             <br />
             <button
                id="register-button"
                onClick={(evt) => {
                    evt.preventDefault();
                    this.sendRegisterRequest();
                }}>
               Register
             </button>
            </form>
        );
    }
}


class Login extends React.Component {

    sendLoginRequest() {
        let formData = new FormData( document.querySelector('#login-form') );
        fetch('/api/login/', {
            method: 'POST',
            body: formData
        })
        .then(result => result.text())
        .then(
            (result) => {
                if (result == 'ok') {
                    this.props.onLogin();
                }
                else {
                    alert('Bad username/password combo');
                }
            },
            (error) => {
                alert('General login error: ' + error);
            }
        )
    }

    render() {
        return (
            <form id="login-form">
             <input
                name="username"
                id="username"
                type="text"
                placeholder="username" />
             <input
                name="password"
                id="password"
                type="password"
                placeholder="password" />
             <br />
             <button
                id="login-button"
                onClick={(evt) => {
                    evt.preventDefault();
                    this.sendLoginRequest();
                }}>
               Login
             </button>
            </form>
        );
    }
}


class Computer extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            isReserved: this.props.computer.isReserved,
            isLoaded: false,
            error: null,
        };

       this.onReserve = this.onReserve.bind(this);
       this.onRelease = this.onRelease.bind(this);
    }

    onReserve() {
  
      console.log(this.props.computer.id)

      //fetch('/api/reserve/' + parseInt(this.props.computer.id) + '/', {
      fetch('/api/reserve/' + this.props.computer.id + '/', {
        method: 'PUT',
      })
      .then(result => result.text())
      .then(
          (result) => {
              if (result == 'ok') {
                  this.setState({
                    isReserved : true
                  });
              }
              else {
                  alert('Cannot reserve at this time.');
              }
          },
          (error) => {
              alert('General login error: ' + error);
          }
      )
    };

    onRelease() {

      console.log(this.props.computer.id)

      //fetch('/api/release/' + parseInt(this.props.computer.id) + '/', {
      fetch('/api/release/' + this.props.computer.id + '/', {
        method: 'PUT',
      })
      .then(result => result.text())
      .then(
          (result) => {
              if (result == 'ok') {
                  this.setState({
                    isReserved : false
                  });
              }
              else {
                  alert('Cannot release at this time.');
              }
          },
          (error) => {
              alert('General login error: ' + error);
          }
      )
    };

    componentDidMount() {
      this.setState({
          isLoaded: true
      });
    }

    render() {
        if (this.state.error) {
            return (
                <div>Error: Computers must have been snapped by Thanos.</div>
            );
        }
        else if (!this.state.isLoaded) {
            return (
                <div>Waiting for Computers to assemble...</div>
            );
        }
        else {

          let add_ons; 

          if (this.props.computer.isReserved) {
            add_ons = 
              <div>
                <p>Being used by {this.props.computer.userID}.</p>
                <button onClick={this.onRelease}>Release</button>
              </div>;
          }
          else {
            add_ons = 
              <div>
                <p>Not being used currently.</p>
                <button onClick={this.onReserve}>Reserve</button>
              </div>;
          }

          return (
              <div id={this.props.computer.id} className="computer">
                <h5>HPC{this.props.computer.id}:</h5>
                {add_ons}
              </div>
          );
        }
    }
}


class Computers extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            computers: [],
            isLoaded: false,
            error: null,
        };
    }

    componentDidMount() {
        fetch('/api/statuses/')
        .then(result => result.json())
        .then(
            (result) => {
                this.setState({
                    computers: result,
                    isLoaded: true
                });
            },
            (error) => {
                this.setState({
                    error: error,
                    isLoaded: true
                });
            }
        )
    }

    render() {
        if (this.state.error) {
            return (
                <div>Error: Computers must have been snapped by Thanos.</div>
            );
        }
        else if (!this.state.isLoaded) {
            return (
                <div>Waiting for Computers to assemble...</div>
            );
        }
        else {
            return (
                <div id="computers">
                    <h1>Computers Assembled!</h1>
                    <ul>
                        {this.state.computers.map(computer => {

                          return (
                            <li key={computer.id}><Computer computer={computer} /></li>
                          )
                          /*
                            return (
                              //FIXME
                             <li className="computer">
                              <div id={computer.id}>
                                <p>HPC{computer.id}</p>
                                <p>Being used by: {computer.userID}</p>
                                <p>Is reserved: {computer.isReserved}</p>
                              </div>
                             </li>
                            );
                          */
                        })};
                    </ul>
                </div>
            );
        }
    }
}


/*
class Avengers extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            avengers: [],
            isLoaded: false,
            error: null,
        };
    }

    componentDidMount() {
        fetch('/api/avengers')
        .then(result => result.json())
        .then(
            (result) => {
                this.setState({
                    avengers: result,
                    isLoaded: true
                });
            },
            (error) => {
                this.setState({
                    error: error,
                    isLoaded: true
                });
            }
        )
    }

    render() {
        if (this.state.error) {
            return (
                <div>Error: Avengers must have been snapped by Thanos.</div>
            );
        }
        else if (!this.state.isLoaded) {
            return (
                <div>Waiting for Avengers to assemble...</div>
            );
        }
        else {
            return (
                <div className="avengers">
                    <h1>Avengers Assembled!</h1>
                    <ul>
                        {this.state.avengers.map(hero => {
                            return (
                             <li key={hero}>
                                {hero}
                             </li>
                            );
                        })};
                    </ul>
                </div>
            );
        }
    }
}
*/


class App extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            //view: 'login'
            view: 'register'
        };
    }

    onRegister() {
      this.setState({
        view: 'login'
      });
    }

    onLogin() {
        this.setState({
            view: 'computers'
        });
    }

    render() {
        let component = <Register onRegister={() => this.onRegister()} />;
        if (this.state.view == 'login') {
            component = <Login onLogin={() => this.onLogin()} />;
        }
        else if (this.state.view == 'computers') {
            component = <Computers />;
        }

        return (
            <div className="app">
              {component}
            </div>
        );
    }
}

const container = document.querySelector('#app');
const root = ReactDOM.createRoot(container);
root.render(<App />);
