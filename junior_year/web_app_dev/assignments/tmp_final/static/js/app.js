// This is a component that displays the form for registering a new user
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


// This is a component that displays a form to login
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


// This is a component to represent a computer. It has methods:
//  onReserve() -> calls /api/reserve/<computer_id>/
//  onRelease() -> calls /api/release/<computer_id>/
//  updateComputer() -> calls /api/status/<computer_id>/ which updates the state
//    of the computer
class Computer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
        isLoaded: false,
        computer: this.props.computer,
        needsUpdate: false,
        error: null,
    };

    this.onReserve = this.onReserve.bind(this);
    this.onRelease = this.onRelease.bind(this);
    this.updateComputer = this.updateComputer.bind(this);
  }


  componentDidMount() {
    this.setState({
        isLoaded: true
    });
  }


  updateComputer() {
    fetch('/api/status/' + this.state.computer.id + '/')
      .then(result => result.json())
      .then(
        (result) => {
          this.setState({
            computer: result,
          });
        },
        (error) => {
          this.setState({
            error: error,
          });
        }
      )
  }


  onReserve() {
    fetch('/api/reserve/' + this.props.computer.id + '/', {
      method: 'PUT',
    })
      .then(result => result.text())
      .then(
        (result) => {
          if (result == 'ok') {
            this.updateComputer();
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
    fetch('/api/release/' + this.props.computer.id + '/', {
      method: 'PUT',
    })
      .then(result => result.text())
      .then(
        (result) => {
          if (result == 'ok') {
            this.updateComputer();
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


  render() {
    if (this.state.error) {
      return (
        <div>Error: Computer {this.props.computer.id}  must have been snapped by Thanos.</div>
      );
    }
    else if (!this.state.isLoaded) {
      return (
        <div>Waiting for Computer {this.props.computer.id} to assemble...</div>
      );
    }
    else {

      let add_ons; 

      if (this.state.computer.isReserved) {
        add_ons = 
          <div className="computer-contents">
            <p><strong>Reserved by: {this.state.computer.user.username}</strong></p>
            <button className="computer-button" onClick={this.onRelease}>Release</button>
          </div>;
      }
      else {
        add_ons = 
          <div className="computer-contents">
            <p><strong>Available</strong></p>
            <button className="computer-button" onClick={this.onReserve}>Reserve</button>
          </div>;
      }

      let status;
      if (this.state.computer.isReserved) {
        status = "true";
      }
      else {
        status = "false";
      }

      return (
        <div id={this.state.computer.id} state={status} className="computer">
          <h5>HPC{this.state.computer.id}:</h5>
          {add_ons}
        </div>
      );
    }
  }
}


// This is a component to represent the list of computers. It has methods:
//  componentDidMount() -> calls /api/statuses/ which fetches the statuses of 
//    all computers and creates a list of computer components
//  updateComputers() -> does the same thing as componentDidMount but this 
//    function will serve as the function we use to update the view every 30sec
class Computers extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      computers: [],
      isLoaded: false,
      error: null,
    };

    this.updateComputers = this.updateComputers.bind(this);
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

    // This code refreshes  the component every 30 seconds
    this.timer = setInterval( () => {
      this.updateComputers();
    }, 30000)
  }

  updateComputers() {
    //console.log('UPDATED COMPUTERS');
    fetch('/api/statuses/')
      .then(result => result.json())
      .then(
        (result) => {
          this.setState({
            computers: result,
          });
        },
        (error) => {
          this.setState({
            error: error,
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
          <button onClick={this.updateComputers}>Refresh Computers</button>
          <div id="container">
            {this.state.computers.map(computer => {
              return (
                <Computer key={computer.id} computer={computer} />
              )
            })}
          </div>
        </div>
      );
    }
  }
}


class App extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      view: 'register',
    };

    this.goToRegister = this.goToRegister.bind(this);
    this.goToLogin = this.goToLogin.bind(this);
    this.onLogout = this.onLogout.bind(this);

    this.computers = React.createRef();
  }


  goToLogin() {
    this.setState({
      view: 'login'
    });
  }


  goToRegister() {
    this.setState({
      view: 'register'
    });
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


  onLogout() {
    fetch('/api/logout/')
      .then(result => result.text())
      .then(
        (result) => {
          if (result == 'ok') {
            this.setState({
              view: 'login'
            });
          }
        },
        (error) => {
          alert('Failed to logout: ' + error);
        }
      )
  }

  render() {

    let component;

    if (this.state.view == 'register') {
      component = <Register onRegister={() => this.onRegister()} />;
    }
    else if (this.state.view == 'login') {
      component = <Login onLogin={() => this.onLogin()} />;
    }
    else if (this.state.view == 'computers') {
      component = <Computers ref={this.computers} />;
    }


    let nav_bar_component = <button onClick={this.goToLogin}>Go To Login</button>;
    if (this.state.view == 'login') {
      nav_bar_component = <button onClick={this.goToRegister}>Go To Register</button>;
    }
    else if (this.state.view == 'computers') {
      nav_bar_component = <button onClick={this.onLogout}>Logout</button>;
    }

    let nav_bar =
      <div id="nav_bar">
        {nav_bar_component}
      </div>;

    return (
      <div className="app">
        {nav_bar}
        {component}
      </div>
    );
  }
}

const container = document.querySelector('#app');
const root = ReactDOM.createRoot(container);
root.render(<App />);
